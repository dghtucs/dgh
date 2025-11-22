

# 编译基础

![alt text](image.png)
![alt text](image-1.png)
![alt text](image-2.png)

![alt text](image-3.png)
![alt text](image-4.png)
![alt text](image-5.png)
![alt text](image-6.png)

![alt text](image-7.png)

# 词法 文法

![alt text](image-9.png)
![alt text](image-8.png)
![alt text](image-10.png)
![alt text](image-11.png)
![alt text](image-12.png)
![alt text](image-13.png)
![alt text](image-14.png)

## 文法的分类

![alt text](image-15.png)

![alt text](image-16.png)
![alt text](image-17.png)

![alt text](image-18.png)
![alt text](image-19.png)

![alt text](image-20.png)

## CFG分析树

![alt text](image-21.png)
![alt text](image-22.png)



# 词法分析


## 正则表达式

![alt text](image-23.png)
![alt text](image-24.png)

![alt text](image-25.png)
![alt text](image-26.png)
![alt text](image-27.png)
![alt text](image-28.png)

![alt text](image-29.png)
### 有穷自动机

![alt text](image-30.png)
![alt text](image-31.png)

### DFA
![alt text](image-31.png)
![alt text](image-32.png)
![alt text](image-33.png)

![alt text](image-34.png)
![alt text](image-36.png)

![alt text](image-37.png)

![alt text](image-38.png)

# 词法分析

![alt text](image-39.png)


![alt text](image-40.png)
## 正则表达式到NFA
![alt text](image-41.png)

## NFA到DFA

![alt text](image-42.png)
![alt text](image-43.png)

## 识别单词的DFA

![Alt text](image-45.png)
![Alt text](image-46.png)


# 自顶向下分析

![Alt text](image-47.png)
最左推导


最右规约
![Alt text](image-49.png)

自底向上使用最左规约，因此称为规范规约
![Alt text](image-50.png)


![Alt text](image-51.png)

# 文法转换

![Alt text](image-52.png)

左递归
![Alt text](image-53.png)

消除左递归
![Alt text](image-54.png)

![Alt text](image-55.png)

间接左递归
![Alt text](image-56.png)

![Alt text](image-57.png)


提取左公因子
![Alt text](image-58.png)



# LL(1)文法
s文法
![Alt text](image-60.png)

FOLLOW集合
![Alt text](image-61.png)

q文法
![Alt text](image-62.png)


FIRST集合
![Alt text](image-63.png)


![Alt text](image-64.png)

LL(1)文法
![Alt text](image-65.png)


# FOLLOW集合FIRST集合计算

first
![Alt text](image-66.png)

![Alt text](image-67.png)

![Alt text](image-68.png)

follow
![Alt text](image-69.png)


这个分析过程要反复学习
https://www.bilibili.com/video/BV1dL4y1H7T8?t=588.9&p=22

要持续更新
![Alt text](image-70.png)

![Alt text](image-71.png)


select集合
![Alt text](image-72.png)
不相交就是LL1文法

进行预测分析
![Alt text](image-73.png)

# 递归预测
![Alt text](image-74.png)

![Alt text](image-75.png)

# 非递归预测


$$ r_i = \alpha_i + \beta_i \cdot F + \epsilon_i $$






















