#include<stdio.h>
#include<malloc.h>
#include<string.h>

const int BUFFER = 1024;

struct node {
    /**
     * 1 - symbol
     * 2 - float
     * */ 
    int type;
    char sym;
    float val;
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
    if (v1 > v2)
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

float parse_figure(char* exp, int* cnt) {
    float ret = 0;
    for (int i = *cnt; i < BUFFER; i++) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            ret = ret * 10 + (exp[i] - '0');
        } else if (exp[i] == '.') {
            i++;
            ret += parse_figure_float(exp, &i);
            *cnt = i - 1;
            break;
        } else {
            *cnt = i - 1;
            break;
        }
    }
    return ret;
}

int parse(char* exp) {
    int ret;
    int s1p = 0, s2p = 0, s3p = 0;
    struct node s1[BUFFER], s2[BUFFER], s3[BUFFER];

    s1[s1p].type = 1;
    s1[s1p].sym = '#';
    s1p++; 
        
    for (int i=0; i < BUFFER; i++) {
        if ((exp[i] >= '0' && exp[i] <= '9')) {
            s2[s2p].type = 2;
            s2[s2p].val = parse_figure(exp, &i);
            s2p++;
        } else if (exp[i] == '+' || exp[i] == '-' || 
                   exp[i] == '*' || exp[i] == '/') {
            while(1) {
                if (s1p < 1)
                    break;
                if (prio_check(exp[i], s1[s1p-1].sym) == 1) {
                    s1[s1p].type = 1;
                    s1[s1p].sym = exp[i];
                    s1p++;
                    break;
                } else {
                    s2[s2p].type = 1;
                    s2[s2p].sym = s1[s1p--].sym;
                    s2p++;
                }
            }
        } else if (exp[i] == '(') {
            s1[s1p].type = 1;
            s1[s1p].sym = exp[i];
            s1p++;
        } else if (exp[i] == ')') {
            while(1) {
                if (s1p < 1)
                    break;
                if (s1[s1p-1].sym != '(') {
                    s2[s2p].type = 1;
                    s2[s2p].sym = s1[s1p--].sym;
                    s2p++;
                } else {
                    s1p--;
                    break;
                }
            }
        } else if (exp[i] == ' ' || exp[i] == '\t') {
            /* do nothing */
        } else if (exp[i] == '=' || exp[i] == '\n' ||
                   exp[i] == '\0') {
            while(1) {
                if (s1p == 1)
                    break;
                s2[s2p].type = 1;
                s2[s2p].sym = s1[s1p--].sym;
                s2p++;
            }
            break;
        } else {
            fprintf(stderr,"Syntax Error.\n");
            return -1;
        }
    }

    for (int i=0; i < s1p; i++) {
        printf("s1[%d] type=%d, sym=%c, val=%f\n", i, s1[i].type, s1[i].sym, s1[i].val);
    }
    for (int i=0; i < s2p; i++) {
        printf("s2[%d] type=%d, sym=%c, val=%f\n", i, s2[i].type, s2[i].sym, s2[i].val);
    }

    for (int i = 0; i < s2p; i++) {
        struct node n = s2[i];
        if (n.type == 1) {
            if (n.sym == '+') {
                if (s3p < 2) {
                    fprintf(stderr,"Syntax Error.\n");
                    return -1;
                }
                s3[s3p-2].val += s3[s3p-1].val;
                s3p--;
            } else if (n.sym == '-') {
                if (s3p < 2) {
                    fprintf(stderr,"Syntax Error.\n");
                    return -1;
                }
                s3[s3p-2].val -= s3[s3p-1].val;
                s3p--;
            } else if (n.sym == '*') {
                if (s3p < 2) {
                    fprintf(stderr,"Syntax Error.\n");
                    return -1;
                }
                s3[s3p-2].val *= s3[s3p-1].val;
                s3p--;
            } else if (n.sym == '/') {
                if (s3p < 2) {
                    fprintf(stderr,"Syntax Error.\n");
                    return -1;
                }
                s3[s3p-2].val /= s3[s3p-1].val;
                s3p--;
            } else {
                fprintf(stderr,"Syntax Error.\n");
                return -1;
            }
        } else {
            s3[s3p].type = n.type;
            s3[s3p].val = n.val;
            s3p++;
        }
    }
    if (s3p != 1) {
        fprintf(stderr,"Syntax Error.\n");
        return -1;
    } else {
        fprintf(stderr, "%s %f\n", exp, s3[1].val);
    }
    return 0;
}


int main(int argc, char* argv[]) {
    char *exp;
    exp = (char*)malloc(sizeof(char) * BUFFER);

    while(1) {
        fprintf(stdout, "EXPRESSION= ");
        fgets(exp, BUFFER, stdin);
        if (exp[0]=='e'&&exp[1]=='x'&&exp[2]=='i'&&exp[3]=='t')
            break;
        parse(exp);
    }

    free(exp);
    return 0;
}
