import json
import os
from collections import defaultdict
from pypinyin import lazy_pinyin, Style

def extract_hanzi(text):
    """
    从文本中提取所有汉字
    """
    return ''.join(filter(lambda x: '\u4e00' <= x <= '\u9fff', text))


def load_existing_data(file_path):
    """
    加载已存在的数据，如果文件不存在，返回一个空字典
    """
    if os.path.exists(file_path):
        with open(file_path, 'r', encoding='utf-8') as file:
            return json.load(file)
    else:
        return {}


def hanzi_to_pinyin_counts(file_path, existing_data):
    # 初始化一个字典来存储结果，如果存在已有数据，则加载它
    pinyin_dict = defaultdict(lambda: defaultdict(int), existing_data)
    
    # 调整字典结构以适应新增数据的处理方式
    for pinyin, info in pinyin_dict.items():
        char_counts = defaultdict(int, zip(info['words'], info['counts']))
        pinyin_dict[pinyin] = char_counts

    # 以行为单位读取并解析文件
    with open(file_path, 'r', encoding='GBK') as file:
        for line in file:
            hanzi_text = extract_hanzi(line)
            for char in hanzi_text:
                pinyin = ''.join(lazy_pinyin(char, style=Style.NORMAL))
                pinyin_dict[pinyin][char] += 1
    
    # 调整数据结构以适应最终输出格式
    results = {}
    for pinyin, chars in pinyin_dict.items():
        results[pinyin] = {
            "words": list(chars.keys()),
            "counts": list(chars.values())
        }       
    return results

def term_to_pinyin_counts(file_path, existing_data):
    # 初始化一个字典来存储结果，如果存在已有数据，则加载它
    pinyin_dict = defaultdict(lambda: defaultdict(int), existing_data)
    
    # 调整字典结构以适应新增数据的处理方式
    for pinyin, info in pinyin_dict.items():
        char_counts = defaultdict(int, zip(info['words'], info['counts']))
        pinyin_dict[pinyin] = char_counts

    # 以行为单位读取并解析文件
    with open(file_path, 'r', encoding='GBK') as file:
        for line in file:
            hanzi_text = extract_hanzi(line)
            for i in range(0,len(hanzi_text)-1):
                py1 = ''.join(lazy_pinyin(hanzi_text[i], style=Style.NORMAL))
                py2 = ''.join(lazy_pinyin(hanzi_text[i+1], style=Style.NORMAL))
                py = py1 +' '+py2
                term = hanzi_text[i]+' '+hanzi_text[i+1]
                pinyin_dict[py][term] += 1
            
    
    # 调整数据结构以适应最终输出格式
    results = {}
    for pinyin, chars in pinyin_dict.items():
        results[pinyin] = {
            "words": list(chars.keys()),
            "counts": list(chars.values())
        }       
    return results



def main():
    existing_file_path = '../1_word.txt'
    existing_file_path2 = '../2_word.txt'
    # 如果文件不存在，则新建文件并初始化写入一个空字典
    if not os.path.exists(existing_file_path):
        with open(existing_file_path, 'w') as file:
            file.write('{}')
    if not os.path.exists(existing_file_path2):
        with open(existing_file_path2, 'w') as file:
            file.write('{}')
    
    for i in range(4,12):
        
        file_path = f'../sina_news_gbk/2016-{i:02}.txt'
        
        existing_data = load_existing_data(existing_file_path)
        existing_data2 = load_existing_data(existing_file_path2)
        result = hanzi_to_pinyin_counts(file_path, existing_data)
        result2 = term_to_pinyin_counts(file_path,existing_data2)
        
        # 将结果保存到同一个 JSON 文件中，更新或新增数据
        with open(existing_file_path, 'w', encoding='utf-8') as file:
            json.dump(result, file, ensure_ascii=False, indent=4)
        with open(existing_file_path2, 'w', encoding='utf-8') as file:
            json.dump(result2, file, ensure_ascii=False, indent=4)
        print(f"2016-{i:02}月拼音统计完成，结果已保存到 1_word.txt 2_word.txt")
    print("新浪新闻数据训练完毕！")

if __name__ == "__main__":
    main()
