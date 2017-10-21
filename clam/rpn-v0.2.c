#include<stdio.h>
#include<malloc.h>
#include<string.h>

const int BUFFER = 1024;

struct node {
    /**
     * 1 - symbol
     * 2 - int
     * 3 - float
     * */ 
    int type;
    void *data;
};

/* if c1 > c2, return 1 else return 0 */
int prio_check(char c1, char c2) {
    int symbol[7][2] = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},
                        {'(', 3}, {')', 3}, {'#', 0}};
    int v1, v2;
    for (int i=0; i < 7; i++) {
        if (symbol[i][0] == c1) {
            v1 = symbol[i][1];
            break;
        }
    }
    for (int i=0; i < 7; i++) {
        if (symbol[i][0] == c2) {
            v2 = symbol[i][1];
            break;
        }
    }
    if (c1 > c2)
        return 1;
    return 0;
}

/** 
 * exp - inputed str
 * cnt - point to current position of exp
 *       the begining of float part
 * return - float parsed
 * cnt point to the next of float part
 * */
float parse_figure_float(char* exp, int* cnt) {
    float ret = 0;
    float bit = 0.1;
    for (int i = *cnt; i < BUFFER; i++) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            ret = ret + bit * (exp[i] - '0');
            bit *= 0.1;
        } else {
            *cnt = i;
            break;
        }
    }
    return ret;
}

int parse_figure(char* exp, int* cnt, float* flt, int* itg) {
    int pt_int = 0;
    float pt_flt = 0;
    for (int i = *cnt; i < BUFFER; i++) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            pt_int = pt_int * 10 + exp[i] - '0';
        } else if (exp[i] == '.') {
            i++;
            pt_flt = parse_figure_float(exp, &i);
            *cnt = i - 1;
            break;
        } else {
            *cnt = i - 1;
            break;
        }
    }
    if (pt_flt == 0) {
        *itg = pt_int;
        return 0;
    }
    *flt = pt_int + pt_flt;
    return 1;
}

int parse(char* exp, int** datas) {
    int ret;
    float *flts;
    char *chrs;
    int *ints;
    flts = (float*)datas[0];
    chrs = (char*)datas[1];
    ints = datas[2];
    int s1p = 0, s2p = 0, s3p = 0;
    struct node s1[BUFFER], s2[BUFFER], s3[BUFFER];
    int cnt_flts = 0, cnt_chrs = 0, cnt_ints = 0;

    chrs[cnt_chrs] = '#';
    s1[s1p].type = 1;
    s1[s1p].data = &chrs[cnt_chrs];
    s1p++; 
    cnt_chrs++;
        
    for (int i=0; i < BUFFER; i++) {
        if ((exp[i] >= '0' && exp[i] <= '9')) {
            ret = parse_figure(exp, &i, &flts[cnt_flts], 
                    &ints[cnt_ints]);
            if (ret == 1) {
                printf("%f\n", flts[cnt_flts]);
                s2[s2p].type = 3;
                s2[s2p].data = &flts[cnt_flts];
                s2p++;
                cnt_flts++;
            } else {
                printf("%d\n", ints[cnt_ints]);
                s2[s2p].type = 2;
                s2[s2p].data = &ints[cnt_ints];
                s2p++;
                cnt_ints++;
            }
        } else if (exp[i] == '+' || exp[i] == '-' || 
                   exp[i] == '*' || exp[i] == '/' || 
                   exp[i] == '(' || exp[i] == ')') {
            chrs[cnt_chrs] = exp[i];
            while(1) {
                if (s1p == 0)
                    break;
                if (prio_check(exp[i], *(int*)(s1[s1p-1].data))) {
                    s1[s1p].type = 1;
                    s1[s1p].data = &chrs[cnt_chrs];
                    s1p++;
                    break;
                } else {
                    s2[s2p].type = 1;
                    s2[s2p].data = s1[s1p-1].data;
                    s2p++;
                    s1p--;
                }
            }
            cnt_chrs++;
        } else if (exp[i] == ' ' || exp[i] == '\t') {
            /* do nothing */
        } else if (exp[i] == '=' || exp[i] == '\n' ||
                   exp[i] == '\0') {
            while(1) {
                if (s1p == 1)
                    break;
                s2[s2p].type = 1;
                s2[s2p].data = s1[s1p-1].data;
                s2p++;
                s1p--;
            }
            break;
        } else {
            fprintf(stderr,"Syntax Error.\n");
            return -1;
        }
    }
    for (int i = 0; i < s2p; i++) {
        struct node n = s2[i];
        if (n.type == 1) {
            if (*(char*)(n.data) == '+') {
                if (s3p < 2) {
                    fprintf(stderr,"Syntax Error.\n");
                    return -1;
                }
                *(int*)(s3[s3p-2].data) += *(int*)(s3[s3p-1].data);
                s3p--;
            } else if (*(char*)(n.data) == '-') {
                if (s3p < 2) {
                    fprintf(stderr,"Syntax Error.\n");
                    return -1;
                }
                *(int*)(s3[s3p-2].data) -= *(int*)(s3[s3p-1].data);
                s3p--;
            } else if (*(char*)(n.data) == '*') {
                if (s3p < 2) {
                    fprintf(stderr,"Syntax Error.\n");
                    return -1;
                }
                *(int*)(s3[s3p-2].data) *= *(int*)(s3[s3p-1].data);
                s3p--;
            } else if (*(char*)(n.data) == '/') {
                if (s3p < 2) {
                    fprintf(stderr,"Syntax Error.\n");
                    return -1;
                }
                *(int*)(s3[s3p-2].data) /= *(int*)(s3[s3p-1].data);
                s3p--;
            } else {
                fprintf(stderr,"Syntax Error.\n");
                return -1;
            }
        } else {
            s3[s3p].type = n.type;
            s3[s3p].data = n.data;
            s3p++;
        }
    }
    if (s3p != 1) {
        fprintf(stderr,"Syntax Error.\n");
        return -1;
    } else {
        fprintf(stderr, "%s %f\n", exp, *(int*)(s3[1].data));
    }
    return 0;
}


int main(int argc, char* argv[]) {
    char *exp;
    float *flts;
    char *chrs;
    int *ints;
    exp = (char*)malloc(sizeof(char) * BUFFER);
    flts = (float*)malloc(sizeof(float) * BUFFER);
    chrs = (char*)malloc(sizeof(char) * BUFFER);
    ints = (int*)malloc(sizeof(int) * BUFFER);
    int* datas[3];
    datas[0] = (int*)flts;
    datas[1] = (int*)chrs;
    datas[2] = ints;

    while(1) {
        fprintf(stdout, "EXPRESSION= ");
        fgets(exp, BUFFER, stdin);
        if (exp[0]=='e'&&exp[1]=='x'&&exp[2]=='i'&&exp[3]=='t')
            break;
        parse(exp, datas);
    }

    free(exp);
    free(flts);
    free(chrs);
    free(ints);
    return 0;
}
