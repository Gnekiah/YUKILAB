import os, time
from urllib import request

zsurl = "http://q.stock.sohu.com/hisHq?code=zs_%s&start=19900101&end=20180101"
ggurl = "http://q.stock.sohu.com/hisHq?code=cn_%s&start=19900101&end=20180101"

## 根据url抓取页面内容，主要是json数据
## 返回抓到的json格式数据，内容是某个股票的历史数据，数据格式为：
## 日期/开/收/涨跌/涨跌幅/低/高/成交量/成交额/换手率
def creeper(url):
    resp = request.urlopen(url)
    html = resp.read()
    return html
    
## 将抓取的json内容保存到指定的文件中
def save(text, fname):
    with open(fname, "ab") as f:
        f.write(text)
    return

## 遍历股票ID，将所有股票的历史交易数据下载来并保存到对应ID的文件中
def main():
    index_list = list()
    with open("indiv.txt", "rt") as f:
        for i in f:
            index_list.append(i.split(" ")[0])
    for item in index_list:
        ret = creeper(ggurl % item)
        save(ret, "cn_%s.json" % item)
        time.sleep(2)
    return

## 获取所有的个股代码，保存为indiv.txt
def init():
    indiv = list()
    text = str()
    with open("a.txt", "rt") as f:
        text = f.readline().replace(" ", "")
    lines = text.split(")")
    for i in lines:
        if i == "" or i == None:
            pass
        tmp = i.split("(")
        if len(tmp) != 2:
            continue
        indiv.append([tmp[1], tmp[0]])
    with open("indiv.txt", "at") as f:
        for i in indiv:
            f.write("%s %s\n" % (i[0], i[1]))
    return
    
if __name__ == "__main__":
    print("=====> Begin")
    main()
    print("=====> End")