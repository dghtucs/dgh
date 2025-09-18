import json
import time
def read_data():

    
    # 读取一元词汇表
    with open('../1_word.txt', 'r', encoding='utf-8') as file:
        one_word_data = json.load(file)
    
    # 读取二元词汇表
    with open('../2_word.txt', 'r', encoding='utf-8') as file:
        two_word_data = json.load(file)
    
    return one_word_data, two_word_data

# 计算二元组概率
def calculate_probability(term_counts, word_counts, prev_word, word):
    bi_gram = prev_word + ' ' + word
    bi_gram_count = term_counts.get(bi_gram, 0)
    prev_word_count = word_counts.get(prev_word, 0)
    if prev_word_count > 0:
        return bi_gram_count / prev_word_count
    else:
        return 0

def viterbi(pinyin_sequence, one_word_data, two_word_data, word_counts, term_counts):
    dp = [{}]
    path = {}
    k = 5000  # 每次扩展的节点数
    # 初始化路径字典
    path = {}
    
    # 初始化首个拼音对应的所有汉字的概率
    for word in one_word_data[pinyin_sequence[0]]['words']: 
        dp[0][word] = word_counts.get(word, 0)  # 假设初始概率，使用字出现的次数
        path[word] = [word]

    # 开始循环处理后续拼音
    for i in range(1, len(pinyin_sequence)):
        dp.append({})
        newpath = {}

        # 为当前拼音的每个字生成可能的前缀
        current_pinyin_words = one_word_data[pinyin_sequence[i]]['words']
        prev_pinyin_words = one_word_data[pinyin_sequence[i-1]]['words']
        all_probabilities = []

        # for word in current_pinyin_words:
        #     # 生成(word, 概率, 最佳前一个字)的列表
        #     probabilities = [
        #         (dp[i-1][prev_word] * calculate_probability(term_counts, word_counts, prev_word, word), prev_word)
        #         for prev_word in prev_pinyin_words
        #     ]
        #     # 取最大概率及对应的前一个字
        #     max_prob, best_prev_word = max(probabilities, key=lambda x: x[0])
        #     all_probabilities.append((max_prob, word, best_prev_word))
        
        for word in current_pinyin_words:
            probabilities = []
            for prev_word in prev_pinyin_words:
                if prev_word in dp[i-1]:  # 检查 prev_word 是否在 dp[i-1] 中
                    prob = dp[i-1][prev_word] * calculate_probability(term_counts, word_counts, prev_word, word)
                    probabilities.append((prob, prev_word))
            if probabilities:  # 确保列表不为空
                max_prob, best_prev_word = max(probabilities, key=lambda x: x[0])
                all_probabilities.append((max_prob, word, best_prev_word))

        # 按概率排序并取前k个
        best_probabilities = sorted(all_probabilities, key=lambda x: x[0], reverse=True)[:k]
        
        for max_prob, word, best_prev_word in best_probabilities:
            dp[i][word] = max_prob
            newpath[word] = path[best_prev_word] + [word]

        path = newpath

    # 选择概率最大的最终路径
    final_probabilities = [(dp[len(pinyin_sequence)-1][word], word) for word in dp[len(pinyin_sequence)-1]]
    max_prob, last_word = max(final_probabilities, key=lambda x: x[0])

    # 检查 last_word 是否在 path 中，避免 KeyError
    if last_word in path:
        return ''.join(path[last_word])
    else:
    # 处理 last_word 不在 path 中的情况，例如返回错误消息或空字符串
        return "1"




# 主函数中检查pinyin_sequence是否为空
def main():
    start_time = time.time()
    # 首先读入数据
    one_word_data, two_word_data = read_data()
    # 初始化
    

    # 每个汉字的出现次数
    word_counts = {}
    for key,value in one_word_data.items():
        for word, count in zip(value['words'], value['counts']):
            # 遍历每个字，并累加它出现的次数
            word_counts[word] = word_counts.get(word, 0) + count
    
    # 每个词出现的次数
    term_counts = {}
    for key,value in two_word_data.items():
        for word,count in zip(value['words'],value['counts']):
            # 遍历每个词
            term_counts[word] = term_counts.get(word,0) + count
    try:
        while True:
            input_line = input().strip()
            if not input_line:
                break
            pinyin_sequence = input_line.split()
            pinyin_sequence = ['lve' if pinyin == 'lue' else pinyin for pinyin in pinyin_sequence]
            if pinyin_sequence:  # 确保不是空列表
                result = viterbi(pinyin_sequence, one_word_data, two_word_data,word_counts,term_counts)
                print(result)
    except EOFError:
        pass
    end_time = time.time()
    runtime = end_time - start_time
    # print("程序运行时间:", runtime, "秒")


if __name__ == "__main__":
    main()
