#!/bin/python2.7

DEBUG = True

def debug(info, flag=True):
    if not flag: return
    if DEBUG: print "DEBUG:", info


def parse_figure(exp):
    ret = 0
    while exp:
        item = exp.pop(0)
        if item.isdigit():
            ret = ret * 10 + int(item)
        else:
            exp.insert(0, item)
            break
    return ret


def prio_check(c1, c2):
    mat = {'+':1,'-':1,'*':2,'/':2,'(':3,')':3,'#':0}
    if mat[c1] > mat[c2]:
        return True
    return False


def parse(exp):
    s = [[],[]]
    exp = list(exp)
    s[0].append('#')
    ## parse expression
    while exp:
        item = exp.pop(0)
        ## parse digit
        if item.isdigit():
            exp.insert(0, item)
            s[1].append(parse_figure(exp))
        ## parse symbol
        elif item in "+-*/":
            while s[0]:
                items = s[0].pop()
                if prio_check(item, items) or items == '(':
                    s[0].append(items)
                    s[0].append(item)
                    break
                else:
                    s[1].append(items)
        ## parse (
        elif item == '(':
            s[0].append(item)
        ## parse )
        elif item == ')':
            while s[0]:
                items = s[0].pop()
                if items == '#':
                    print("Syntax Error! in ')'")
                    break
                elif items == '(':
                    break
                else:
                    s[1].append(items)
        ## parse space and tab
        elif item in ' \t':
            pass
        ## parse \n \0 \r #
        elif item in '=\n\0\r#':
            while s[0]:
                items = s[0].pop()
                if items == '#':
                    break
                s[1].append(items)
        ## other case
        else:
            print("Syntax Error!")
            break
    ## push s[0] all to s[1]
    while s[0]:
        item = s[0].pop()
        if item == '#':
            break
        s[1].append(item)
    debug(s)
    ## do calc
    while s[1]:
        item = s[1].pop(0)
        if type(item) == type(1):
            s[0].append(item)
            continue
        if (len(s[0]) < 2):
            print("Syntax Error!")
            break
        v1 = s[0].pop()
        v2 = s[0].pop()
        if item == '+':
            s[0].append(v1+v2)
        elif item == '-':
            s[0].append(v2-v1)
        elif item == '*':
            s[0].append(v1*v2)
        else:
            s[0].append(v2/v1)
    ## check syntax
    if len(s[0]) != 1:
        print("Syntax Error!")
        return
    ## print result
    print "Result=", s[0].pop()


if __name__ == '__main__':
    while(True):
        exp = raw_input("Expression= ")
        if (exp == 'exit'):
            print("GoodBye!")
            break
        parse(exp)
