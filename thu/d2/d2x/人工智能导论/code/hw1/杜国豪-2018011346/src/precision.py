import os



def main():
    with open('../../test/out.txt','r',encoding='utf-8') as file1:
        my_lines = file1.readlines()

    with open('../../test/std_output.txt','r',encoding='utf-8') as file2:
        std_lines = file2.readlines()

    sentences_counts = len(std_lines)
    sentences_right_counts = 0
    word_counts = 0
    for line in std_lines:
        # 统计每一行的字数
        word_counts += len(line.strip())
    word_right_counts = 0
    for sentence1,sentence2 in zip(my_lines,std_lines):
        if sentence1 == sentence2:
            sentences_right_counts += 1
        for word1,word2 in zip(sentence1,sentence2):
            if word1 == word2:
                word_right_counts += 1
    
    word_precision = word_right_counts / word_counts
    sentence_precision = sentences_right_counts / sentences_counts
    print(f'字准确率是：{word_precision}')
    print(f'句准确率是：{sentence_precision}')


if __name__ == '__main__':
    main()


