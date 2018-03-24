import os, time, json

## 筛选出如下数据：
## 涨停时（9-11个点），计算出当天的量比，然后与第二天的数据拼接到一起
## K线数据格式为：
## 个股代码/日期/开/收/涨跌/涨跌幅/低/高/成交量/成交额/换手率
## 输出数据的格式为：
## 涨停日数据/第一天量比/次日数据

def load(f):
    f = "indiv/%s" % f
    text = str()
    with open(f, "rt") as _f:
        text = json.loads(_f.readline())
    hq = text[0]["hq"]
    code = text[0]["code"][3:]
    lines = list()
    for i in hq:
        line = list()
        line.append(code)
        line.extend(i)
        lines.append(line)
    lines.reverse()
    return lines

def calclmr(lines, i):
    x = i - 1
    it = 5
    cnt = 0.0
    while it > 0 and x > 0:
        cnt += int(lines[x][8])
        x -= 1
        it -= 1
    if it == 5:
        return None
    cnt /= (5-it)
    if cnt == 0:
        return None
    lmr = float(lines[i][8]) / cnt
    return lmr

def main():
    result = list()
    files = os.listdir("indiv/")
    for f in files:
        lines = load(f)
        length = len(lines)
        for i in range(length):
            resline = list()
            chg = abs(float(lines[i][5][:-1]))
            ## 涨跌幅在9-11个点之间的数据
            if chg > 9 and chg < 11 and i < length-1:
                lmr = calclmr(lines, i)
                if lmr == None:
                    continue
                resline.extend(lines[i])
                resline.append(lmr)
                resline.extend(lines[i+1])
                result.append(resline)
    with open("result.csv", "at") as f:
        for i in result:
            s = str()
            for j in i:
                s += str(j) + ","
            s = s[:-1] + "\n"
            f.write(s)
    print(len(result))
    return
    
if __name__ == "__main__":
    print("=====> Begin")
    main()
    print("=====> End")
