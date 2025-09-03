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

![alt text](image-15.png)

![alt text](image-16.png)

![alt text](image-17.png)

### 双指针
有两个输入, 两个都需要遍历完

![alt text](image-18.png)

![alt text](image-19.png)

![alt text](image-20.png)

### 滑动窗口

![alt text](image-21.png)

![alt text](image-22.png)

![alt text](image-23.png)

### 构建前缀和

![alt text](image-24.png)

![alt text](image-25.png)

![alt text](image-26.png)


### 高效的字符串构建

![alt text](image-27.png)

![alt text](image-28.png)

![alt text](image-29.png)


### 链表: 快慢指针

![alt text](image-30.png)

![alt text](image-31.png)

![alt text](image-32.png)

### 反转链表
![alt text](image-33.png)

![alt text](image-34.png)

![alt text](image-35.png)

### 找到符合确切条件的子数组数

![alt text](image-36.png)

![alt text](image-37.png)

![alt text](image-38.png)

### 单调递增栈

![alt text](image-39.png)

![alt text](image-40.png)

![alt text](image-41.png)

### 二叉树: DFS (递归)

![alt text](image-42.png)

![alt text](image-43.png)

![alt text](image-44.png)

### 二叉树: DFS (迭代)

```java
public int dfs(TreeNode root) {
    Stack<TreeNode> stack = new Stack<>();
    stack.push(root);
    int ans = 0;

    while (!stack.empty()) {
        TreeNode node = stack.pop();
        // 根据题意补充代码
        if (node.left != null) {
            stack.push(node.left);
        }
        if (node.right != null) {
            stack.push(node.right);
        }
    }

    return ans;
}

```
```cpp
int dfs(TreeNode* root) {
    stack<TreeNode*> stack;
    stack.push(root);
    int ans = 0;

    while (!stack.empty()) {
        TreeNode* node = stack.top();
        stack.pop();
        // 根据题意补充代码
        if (node->left != nullptr) {
            stack.push(node->left);
        }
        if (node->right != nullptr) {
            stack.push(node->right);
        }
    }

    return ans;
}
```


```python
def dfs(root):
    stack = [root]
    ans = 0

    while stack:
        node = stack.pop()
        # 根据题意补充代码
        if node.left:
            stack.append(node.left)
        if node.right:
            stack.append(node.right)

    return ans



```

### 二叉树: BFS

```java
public int fn(TreeNode root) {
    Queue<TreeNode> queue = new LinkedList<>();
    queue.add(root);
    int ans = 0;

    while (!queue.isEmpty()) {
        int currentLength = queue.size();
        // 做一些当前层的操作

        for (int i = 0; i < currentLength; i++) {
            TreeNode node = queue.remove();
            // 根据题意补充代码
            if (node.left != null) {
                queue.add(node.left);
            }
            if (node.right != null) {
                queue.add(node.right);
            }
        }
    }

    return ans;
}


```


































