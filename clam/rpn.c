#include<stdio.h>
#include<malloc.h>
#include<string.h>

const int BUFFER = 1024;

struct node {
    int type;
    void *data;
};


int parse(char* exp, int** datas) {
    float *flts;
    char *chrs;
    int *ints;
    flts = (float*)datas[0];
    chrs = (char*)datas[1];
    ints = datas[2];
    struct node s1[BUFFER], s2[BUFFER], s3[BUFFER];

    for (int i=0; i < BUFFER; i++) {
        int cnt_flts = 0, cnt_chrs = 0, cnt_ints = 0;
        if ((exp[i] >= '0' && exp[i] <= '9') || exp[i] == '.') {
            
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
