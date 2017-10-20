#include<stdio.h>
#include<malloc.h>

const int BUFFER = 256;

struct bnode {
    /* 1 - int
     * 2 - float
     * 3 - char
     * */
    int type;
    void *data;
    struct bnode *left;
    struct bnode *right;
};

void do_parse_figure(char* exp, int *cnt, int *data) {
    int result = 0;

    for (int i = *cnt; i < BUFFER; i++) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            result = result * 10 + exp[i] - '0';
        } else {
            *cnt = i - 1;
            break;
        }
    }
    *data = result;
}

int do_parse(char* exp) {
    int ret = 0;
    struct bnode *tree;
    tree = (struct bnode*)malloc(sizeof(struct bnode));
    tree->left = 0;
    tree->right = 0;

    /* 0123456789+*-/=.() */
    for (int i=0; i < BUFFER; i++) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            int *data;
            data = (int*)malloc(sizeof(int));
            do_parse_figure(exp, &i, data);
            struct bnode *node;
            node = (struct bnode*)malloc(sizeof(struct bnode));
            node->type = 1;
            node->data = data;
            node->left = tree;
            tree->right = node;
            tree = node;
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' ||
                exp[i] == '/' || exp[i] == '(' || exp[i] == ')') {
            char *data;
            data = (char*)malloc(sizeof(char));
            *data = exp[i];
            struct bnode *node;
            node = (struct bnode*)malloc(sizeof(struct bnode));
            node->type = 3;
            node->data = data;
            node->left = tree;
            tree->right = node;
            tree = node;
        } else if (exp[i] == '=') {
            ret = 0;
            goto out;
        } else if (exp[i] == '\n' || exp[i] == '\0') {
            ret = -1;
            goto out;
        } else if (exp[i] == ' ' || exp[i] == '\t') { } else {
            fprintf(stderr,"Syntax error.\n");
            ret = -1;
            goto out;
        }
    }

out:
    while(tree->left != 0) {
        if (tree->type == 1) {
            fprintf(stderr, "%d\n", *(int*)tree->data);
        } else if (tree->type == 2) {
            fprintf(stderr, "%f\n", *(float*)tree->data);
        } else {
            fprintf(stderr, "%c\n", *(char*)tree->data);
        }
        tree = tree->left;
    }
    return ret;
}

int parse_from_input() {
    char *exp;
    int ret = 0;

    exp = (char*)malloc(sizeof(char) * BUFFER);
    if (!exp) {
        fprintf(stderr, "Alloc memory failed.\n");
        ret = -1;
        goto out;
    }
    fprintf(stdout, "EXPRESSION= ");
    fgets(exp, BUFFER, stdin);
    do_parse(exp);  

out:
    free(exp);
    return ret;
}

int parse_from_file(char* fname) {
    char *exp;
    FILE *f;
    int ret = 0;
    
    f = fopen(fname, "r");
    if (!f) {
        fprintf(stderr, "Open file failed.\n");
        ret = -1;
        goto out;
    }
    
    exp = (char*)malloc(sizeof(char) * BUFFER);
    if (!exp) {
        fprintf(stderr, "Alloc memory failed.\n");
        ret = -1;
        goto out;
    }
    
    fgets(exp, BUFFER, f);
    do_parse(exp);  

out:
    fclose(f);
    return ret;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        parse_from_input();
    } else if (argc == 2) {
        parse_from_file(argv[1]);
    } else {
        fprintf(stderr, "ERROR OPTION.");
        return 0;
    }
    return 0;
}
