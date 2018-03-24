import os, time, json

## 整理成indiv.csv，格式为：
## 个股代码/日期/开/收/涨跌/涨跌幅/低/高/成交量/成交额/换手率
def main():
    files = os.listdir("indiv/")
    for f in files:
        f = "indiv/%s" % f
        text = str()
        with open(f, "rt") as _f:
            text = json.loads(_f.readline())
        hq = text[0]["hq"]
        code = text[0]["code"][3:]
        lines = str()
        for i in hq:
            line = code
            for j in i:
                line += "," + j
            lines += line + "\n"
        with open("indiv.csv", "at") as ret:
            ret.write(lines)
    return
    
if __name__ == "__main__":
    print("=====> Begin")
    main()
    print("=====> End")