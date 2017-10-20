#include<stdio.h>
#include<malloc.h>
#include<string.h>

const int BUFFER = 1024;

struct node {
    int type;
    void *data;
};

float parse_figure_float(char* exp, int* cnt) {
    float ret = 0;
    for (int i = *cnt; i < BUFFER; i++) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            float = float * 0.1 + exp[i] - '0';
        } else {
            *cnt = i;
            break;
        }
    }
    return ret;
}

int parse_figure(char* exp, int* cnt, float* flt, int* itg) {
    int pt_int = 0, pt_flt = 0;
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
    *flt = pt_int;

    float tmp = 0;
    while(1) {
        int i = pt_flt % 10;
        tmp = tmp * 0.1 + i;
        pt_flt /= 10;
        if (pt_flt == 0)
            break;
    }
    *flt = *flt + tmp * 0.1;
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

    chrs[0] = '#';
    s1[0].data = &chrs[0];
    s1p++; 
    cnt_chrs++;
        
    for (int i=0; i < BUFFER; i++) {
        if ((exp[i] >= '0' && exp[i] <= '9')) {
            ret = parse_figure(exp, &i, &flts[cnt_flts], 
                    &ints[cnt_ints]);
            if (ret == 1) {
                printf("%f\n", flts[cnt_flts]);
                cnt_flts++;
            } else {
                printf("%d\n", ints[cnt_ints]);
                cnt_ints++;
            }
        } else if (exp[i] == '+' || exp[i] == '-' || 
                   exp[i] == '*' || exp[i] == '/' || 
                   exp[i] == '(' || exp[i] == ')') {
        
        } else if (exp[i] == ' ' || exp[i] == '\t') {
            /* do nothing */
        } else if (exp[i] == '=' || exp[i] == '\n' ||
                   exp[i] == '\0') {
            break;
        } else {
            fprintf(stderr,"Syntax Error.\n");
            return -1;
        }
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
