/*
 * 贪吃蛇原型（24小时之内完成）
 * 初始的贪吃蛇定义为一个1×1的点
 * 给定矩形范围[x,y]，给出贪吃蛇出发点坐标和朝向[x_s, y_s, d_s]
 * d用单个字符表示，为E/S/W/N，对应东南西北
 * 输入操控指令串，操控为L/R/F，对应左、右、前进
 * 输出贪吃蛇经过操控指令之后的坐标和朝向[x_e, y_e, d_e]
 * 可以自由扩展
 * */

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include <pthread.h>
#include <time.h>

/* 贪吃蛇身体节点 */
typedef struct node_t {
    int *p;
    void *next;
} node_t;

int matrix_x = 25;              /* 范围宽 */
int matrix_y = 25;              /* 范围高 */
int start_x = 0;                /* 开始位置X坐标 */
int start_y = 0;                /* 开始位置Y坐标 */
char start_d = 'E';             /* 默认的朝向 */
int end_x = 0;                  /* 移动后的位置X坐标 */
int end_y = 0;                  /* 移动后的位置Y坐标 */
char end_d = 'E';               /* 移动后的朝向 */
int **matrix = NULL;            /* 范围数组 */
int snack_size = 1;             /* 蛇身体长度，长度越长，移动速度越快 */
volatile int exit_sync = 0;     /* 线程同步flag */
pthread_mutex_t mtx;            /* 互斥锁，用于数组的更新 */
node_t *head;                   /* 蛇的头部指针 */

/* 获取控制台输入，直接返回命令符号 */
char getch(void) {
    struct termios tm, tm_old;
    int fd = 0, ch;
    if (tcgetattr(fd, &tm) < 0)
        return -1;
    tm_old = tm;
    cfmakeraw(&tm);
    if (tcsetattr(fd, TCSANOW, &tm) < 0)
        return -1;
    ch = getchar();
    if (tcsetattr(fd, TCSANOW, &tm_old) < 0)
        return -1;
    return ch;
}

/* 检查参数的合法性 */
int check_opts() {
    if (matrix_x <= 0 || matrix_y <= 0) {
        fprintf(stderr, "Bad value: Matrix size of x-axis / y-axis.\n");
        return -1;
    }
    if (start_x < 0 || start_x >= matrix_x || start_y < 0 || start_y >= matrix_y) {
        fprintf(stderr, "Bad value: Start X / Y position out of range.\n");
        return -2;
    }
    if (!(start_d == 'E' || start_d == 'e' || start_d == 'S' || start_d == 's' ||
                start_d == 'W' || start_d == 'w' || start_d == 'N' || start_d == 'n')) {
        fprintf(stderr, "Bad value: Direction cannot parse.\n");
        return -3;
    }
    return 0;
}

/* 打印帮助信息 */
void print_help() {
    fprintf(stderr, "Usage: snake [OPTION]... \nExample: snake -x 25 -y 25 -X 12 -Y 12 -D W\n\n\
        -x          Matrix size of x-axis.\n\
        -y          Matrix size of y-axis.\n\
        -X, --sx    Start X position.\n\
        -Y, --sy    Start Y position.\n\
        -D, --sd    Direction of init.\n\
        -h, --help  Display this help and exit.\n");
}

/* 解析shell传入的选项和参数 */
int parse_opts(int argc, char** argv) {
    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            //print_help();
            return -1;
        }
        else if (strcmp(argv[i], "-x") == 0) {
            if (++i >= argc)
                return -1;
            matrix_x = atoi(argv[i]);
        } 
        else if (strcmp(argv[i], "-y") == 0) {
            if (++i >= argc)
                return -1;
            matrix_y = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "-X") == 0 || strcmp(argv[i], "--sx") == 0) {
            if (++i >= argc)
                return -1;
            start_x = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "-Y") == 0 || strcmp(argv[i], "--sy") == 0) {
            if (++i >= argc)
                return -1;
            start_y = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "-D") == 0 || strcmp(argv[i], "--sd") == 0) {
            if (++i >= argc || strlen(argv[i]) != 1)
                return -1;
            start_d = argv[i][0];
        }
        else {
            return -1;
        }   
        i++;
    }
    return 0;
}

/* 将数组绘制到控制台窗口 */
void draw() {
    int i = 0, j = 0, ch;

    printf("Position: x_e=%d, y_e=%d, d_e=%c        \n\r", end_x, end_y, end_d);

    printf(" ");
    for (i = 0; i < matrix_x; i++)
        printf("_");
    printf(" \n\r|");
    for (i = 0; i < matrix_x; i++)
        printf(" ");
    printf("|\n\r");

    for (i = 0; i < matrix_y; i++) {
        printf("|");
        for (j = 0; j < matrix_x; j++) {
            ch = matrix[i][j];
            switch(ch) {
            case 0:
                printf("\033[32m%c\033[0m", ' ');
                break;
            case 1:
                printf("\033[35m%c\033[0m", '#');
                break;
            case 2:
                printf("\033[31m%c\033[0m", '$');
                break;
            default:
                printf("\033[32m%c\033[0m", ' ');
                break;
            }
        }
        printf("|\n\r");
    }
    
    printf("|");
    for (i = 0; i < matrix_x; i++)
        printf("_");
    printf("|\n\r");

    printf("\033[%dA", matrix_y + 4);
}

/* 改变方向，并朝改变后的方向移动一格 */
void change_direction(char c) {
    if (c == 'L') {
        switch(end_d) {
            case 'N':
                end_d = 'W';
                break;
            case 'W':
                end_d = 'S';
                break;
            case 'S':
                end_d = 'E';
                break;
            case 'E':
                end_d = 'N';
                break;
            default:
                break;
        }
    } 
    else if (c == 'R') {
        switch(end_d) {
            case 'N':
                end_d = 'E';
                break;
            case 'W':
                end_d = 'N';
                break;
            case 'S':
                end_d = 'W';
                break;
            case 'E':
                end_d = 'S';
                break;
            default:
                break;
        }
    }
    switch (end_d) {
        case 'N':
            end_y--;
            break;
        case 'S':
            end_y++;
            break;
        case 'W':
            end_x--;
            break;
        case 'E':
            end_x++;
            break;
        default:
            break;
    }
}

/* 将蛇身体的尾部移动到首部，避免重复malloc/free */
node_t *pop_last() {
    node_t *prev = head;
    node_t *next = head->next;
    if (next == NULL) {
        head = NULL;
        return prev;
    }
    while(next->next) {
        prev = next;
        next = next->next;
    }
    prev->next = NULL;
    return next;
}

/* 随机生成面包，吃了面包后，蛇才能长大 */
void gen_bread() {
    int rx = rand() % matrix_x;
    int ry = rand() % matrix_y;
    
    if (matrix[ry][rx] == 0)
        matrix[ry][rx] = 2;
    else
        gen_bread();
}

/* 响应向左、向右、加速前进的命令 */
void drive(char ctrl) {
    pthread_mutex_lock(&mtx);
    draw();
    node_t *node = NULL;
    change_direction(ctrl);

    if (end_x < 0)
        end_x = matrix_x - 1;
    if (end_x >= matrix_x)
        end_x = 0;
    if (end_y < 0)
        end_y = matrix_y - 1;
    if (end_y >= matrix_y) 
        end_y = 0;
    
    if (matrix[end_y][end_x] == 2) {
        node = (node_t *) malloc(sizeof(node_t));
        gen_bread();
        snack_size++;
    }
    else {
        node = pop_last();
        *node->p = 0;
    }
    node->p = &matrix[end_y][end_x];
    *node->p = 1;
    node->next = head;
    head = node;

    pthread_mutex_unlock(&mtx);
}

/* 子线程定时触发蛇向前移动一格 */
void timer_tick() {
    while (1) {
        if (exit_sync)
            break;
        usleep((int)(100000 + 400000 / sqrt(snack_size)));
        drive('F');
    }
}


int main(int argc, char** argv) {
    int ret = 0, i;
    pthread_t thrd_tick;
    void *retval;
    char ctrl;

    srand((int)time(NULL));
    ret = parse_opts(argc, argv);
    if (ret) {
        print_help();
        return -1;
    }
    ret = check_opts();
    if (ret) 
        return -2;

    matrix = (int **) malloc(sizeof(int*) * matrix_y);
    for (i = 0; i < matrix_y; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * matrix_x);
        memset(matrix[i], 0, sizeof(int) * matrix_x);
    }
    end_x = start_x;
    end_y = start_y;
    end_d = start_d;
    matrix[end_y][end_x] = 1;
    head = (node_t *) malloc(sizeof(node_t));
    head->p = &matrix[end_y][end_x];
    head->next = NULL;
    gen_bread();

    pthread_mutex_init(&mtx, NULL);
    ret = pthread_create(&thrd_tick, NULL, (void*)&timer_tick, NULL);
   
    draw();
    while (1) {
        ctrl = getch();
        if (ctrl == 'q' || ctrl == 'Q')
            break;
        if (ctrl == 'L' || ctrl == 'l' || ctrl == 'A' || ctrl == 'a')
            drive('L');
        else if (ctrl == 'R' || ctrl == 'r' || ctrl == 'D' || ctrl == 'd')
            drive('R');
        else if (ctrl == 'F' || ctrl == 'f' || ctrl == 'W' || ctrl == 'w')
            drive('F');
    }

    exit_sync = 1;
    pthread_join(thrd_tick, &retval);

    printf("\033[%dB", matrix_y + 4);
    printf("Snake: GoodBye!\n");

    for (i = 0; i < matrix_y; i++) 
        free(matrix[i]);
    free(matrix);

    return 0;
}
