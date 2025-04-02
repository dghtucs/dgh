- 将语料库中的sina_news_gbk文件夹放在data文件夹的同级目录
- 运行train.py,将进行数据清洗及抽取，生成1_word.txt和2_word.txt两个文件，为二元模型提供语料
- 运行test.py,进行拼音识别

```
python3 test.py < test/std_input.txt > test/out.txt
```







