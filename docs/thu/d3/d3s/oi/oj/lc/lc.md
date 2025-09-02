here to write my code in leetcode

# 算法面试小抄

## 算法和数据结构

### 时间复杂度


![big-O](image.png)

![alt text](image-1.png)

![alt text](image-2.png)

![alt text](image-3.png)

![alt text](image-4.png)

![alt text](image-5.png)

![alt text](image-6.png)

![alt text](image-7.png)

![alt text](image-8.png)

![alt text](image-9.png)
这张表很全面


### 输入规模

![alt text](image-10.png)

![alt text](image-11.png)

![alt text](image-12.png)

### 排序算法
所有主要的编程语言都有一个内置的排序方法。假设并说排序成本为 O(n⋅logn)。通常是正确的，其中 n 是要排序的元素数。为了完整起见，这里有一个图表，列出了许多常见的排序算法及其完整性。编程语言实现的算法各不相同；例如，Python 使用 Timsort，但在 C++ 中，特定算法不是强制性的并且会有所不同

![alt text](image-13.png)

### 通用DSA流程图

这是一个流程图，可以帮助您确定应该使用哪种数据结构或算法。请注意，此流程图非常笼统，因为不可能涵盖每个场景。

![alt text](image-14.png)

## 算法题代码模板

### 双指针
只有一个输入, 从两端开始遍历

```cpp
int fn(vector<int>& arr) {
    int left = 0;
    int right = int(arr.size()) - 1;
    int ans = 0;

    while (left < right) {
        // 一些根据 letf 和 right 相关的代码补充
        if (CONDITION) {
            left++;
        } else {
            right--;
        }
    }

    return ans;
}

```







