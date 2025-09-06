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

```cpp
int fn(TreeNode* root) {
    queue<TreeNode*> queue;
    queue.push(root);
    int ans = 0;

    while (!queue.empty()) {
        int currentLength = queue.size();
        // 做一些当前层的操作

        for (int i = 0; i < currentLength; i++) {
            TreeNode* node = queue.front();
            queue.pop();
            // 根据题意补充代码
            if (node->left != nullptr) {
                queue.push(node->left);
            }
            if (node->right != nullptr) {
                queue.push(node->right);
            }
        }
    }

    return ans;
}


```

```python
from collections import deque

def fn(root):
    queue = deque([root])
    ans = 0

    while queue:
        current_length = len(queue)
        # 做一些当前层的操作

        for _ in range(current_length):
            node = queue.popleft()
            # 根据题意补充代码
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

    return ans


```

### 图: DFS (递归)
以下图模板假设节点编号从 0 到 n - 1 ，并且图是以邻接表的形式给出的。根据问题的不同，您可能需要在使用模板之前将输入转换为等效的邻接表。

```java
Set<Integer> seen = new HashSet<>();

public int fn(int[][] graph) {
    seen.add(START_NODE);
    return dfs(START_NODE, graph);
}

public int dfs(int node, int[][] graph) {
    int ans = 0;
    // 根据题意补充代码
    for (int neighbor: graph[node]) {
        if (!seen.contains(neighbor)) {
            seen.add(neighbor);
            ans += dfs(neighbor, graph);
        }
    }

    return ans;
}


```

```cpp
unordered_set<int> seen;

int fn(vector<vector<int>>& graph) {
    seen.insert(START_NODE);
    return dfs(START_NODE, graph);
}

int fn dfs(int node, vector<vector<int>>& graph) {
    int ans = 0;
    // 根据题意补充代码
    for (int neighbor: graph[node]) {
        if (seen.find(neighbor) == seen.end()) {
            seen.insert(neighbor);
            ans += dfs(neighbor, graph);
        }
    }

    return ans;
}


```

```python
def fn(graph):
    def dfs(node):
        ans = 0
        # 根据题意补充代码
        for neighbor in graph[node]:
            if neighbor not in seen:
                seen.add(neighbor)
                ans += dfs(neighbor)
        
        return ans

    seen = {START_NODE}
    return dfs(START_NODE)


```

### 图: DFS (迭代)

```java
public int fn(int[][] graph) {
    Stack<Integer> stack = new Stack<>();
    Set<Integer> seen = new HashSet<>();
    stack.push(START_NODE);
    seen.add(START_NODE);
    int ans = 0;

    while (!stack.empty()) {
        int node = stack.pop();
        // 根据题意补充代码
        for (int neighbor: graph[node]) {
            if (!seen.contains(neighbor)) {
                seen.add(neighbor);
                stack.push(neighbor);
            }
        }
    }

    return ans;
}


```

```cpp
int fn(vector<vector<int>>& graph) {
    stack<int> stack;
    unordered_set<int> seen;
    stack.push(START_NODE);
    seen.insert(START_NODE);
    int ans = 0;

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();
        // 根据题意补充代码
        for (int neighbor: graph[node]) {
            if (seen.find(neighbor) == seen.end()) {
                seen.insert(neighbor);
                stack.push(neighbor);
            }
        }
    }
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0el556/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```python
def fn(graph):
    stack = [START_NODE]
    seen = {START_NODE}
    ans = 0

    while stack:
        node = stack.pop()
        # 根据题意补充代码
        for neighbor in graph[node]:
            if neighbor not in seen:
                seen.add(neighbor)
                stack.append(neighbor)
    
    return ans

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0el556/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 图: BFS

```java
public int fn(int[][] graph) {
    Queue<Integer> queue = new LinkedList<>();
    Set<Integer> seen = new HashSet<>();
    queue.add(START_NODE);
    seen.add(START_NODE);
    int ans = 0;

    while (!queue.isEmpty()) {
        int node = queue.remove();
        // 根据题意补充代码
        for (int neighbor: graph[node]) {
            if (!seen.contains(neighbor)) {
                seen.add(neighbor);
                queue.add(neighbor);
            }
        }
    }

    return ans;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0elfx2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```cpp
int fn(vector<vector<int>>& graph) {
    queue<int> queue;
    unordered_set<int> seen;
    queue.add(START_NODE);
    seen.insert(START_NODE);
    int ans = 0;

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        // 根据题意补充代码
        for (int neighbor: graph[node]) {
            if (seen.find(neighbor) == seen.end()) {
                seen.insert(neighbor);
                queue.push(neighbor);
            }
        }
    }
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0elfx2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


```python
from collections import deque

def fn(graph):
    queue = deque([START_NODE])
    seen = {START_NODE}
    ans = 0

    while queue:
        node = queue.popleft()
        # 根据题意补充代码
        for neighbor in graph[node]:
            if neighbor not in seen:
                seen.add(neighbor)
                queue.append(neighbor)
    
    return ans

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0elfx2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


### 找到堆的前 k 个元素

```java
public int[] fn(int[] arr, int k) {
    PriorityQueue<Integer> heap = new PriorityQueue<>(CRITERIA);
    for (int num: arr) {
        heap.add(num);
        if (heap.size() > k) {
            heap.remove();
        }
    }

    int[] ans = new int[k];
    for (int i = 0; i < k; i++) {
        ans[i] = heap.remove();
    }

    return ans;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0eiyfc/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```cpp
vector<int> fn(vector<int>& arr, int k) {
    priority_queue<int, CRITERIA> heap;
    for (int num: arr) {
        heap.push(num);
        if (heap.size() > k) {
            heap.pop();
        }
    }

    vector<int> ans;
    while (heap.size() > 0) {
        ans.push_back(heap.top());
        heap.pop();
    }

    return ans;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0eiyfc/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```python
import heapq

def fn(arr, k):
    heap = []
    for num in arr:
        # 做根据题意补充代码，根据问题的条件来推入堆中
        heapq.heappush(heap, (CRITERIA, num))
        if len(heap) > k:
            heapq.heappop(heap)
    
    return [num for num in heap]

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0eiyfc/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 二分查找

```java
public int fn(int[] arr, int target) {
    int left = 0;
    int right = arr.length - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            // 根据题意补充代码
            return mid;
        }
        if (arr[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    // left 是插入点
    return left;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0eusji/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```cpp
int binarySearch(vector<int>& arr, int target) {
        int left = 0;
        int right = int(arr.size()) - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                // 根据题意补充代码
                return mid;
            }
            if (arr[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        // left 是插入点
        return left;
    }

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0eusji/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```python
def fn(arr, target):
    left = 0
    right = len(arr) - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            # 根据题意补充代码
            return
        if arr[mid] > target:
            right = mid - 1
        else:
            left = mid + 1
    
    # left 是插入点
    return left

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0eusji/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 二分查找: 重复元素，最左边的插入点

```java
public int fn(int[] arr, int target) {
    int left = 0;
    int right = arr.length;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            right = mid
        } else {
            left = mid + 1;
        }
    }

    return left;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0etkbe/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```cpp
int binarySearch(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0etkbe/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```python
def fn(arr, target):
    left = 0
    right = len(arr)
    while left < right:
        mid = (left + right) // 2
        if arr[mid] >= target:
            right = mid
        else:
            left = mid + 1

    return left

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0etkbe/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

### 二分查找: 重复元素，最右边的插入点

```java
public int fn(int[] arr, int target) {
    int left = 0;
    int right = arr.length;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0e83yg/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```cpp
int binarySearch(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0e83yg/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```python
def fn(arr, target):
    left = 0
    right = len(arr)
    while left < right:
        mid = (left + right) // 2
        if arr[mid] > target:
            right = mid
        else:
            left = mid + 1

    return left

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0e83yg/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


### 二分查找: 贪心问题

寻找最小值

```cpp
int fn(vector<int>& arr) {
    int left = MINIMUM_POSSIBLE_ANSWER;
    int right = MAXIMUM_POSSIBLE_ANSWER;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

bool check(int x) {
    // 这个函数的具体实现取决于问题
    return BOOLEAN;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0e3u1v/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


寻找最大值

```cpp
int fn(vector<int>& arr) {
    int left = MINIMUM_POSSIBLE_ANSWER;
    int right = MAXIMUM_POSSIBLE_ANSWER;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return right;
}

bool check(int x) {
    // 这个函数的具体实现取决于问题
    return BOOLEAN;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0e3u1v/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```python
def fn(arr):
    def check(x):
        # 这个函数的具体实现取决于问题
        return BOOLEAN

    left = MINIMUM_POSSIBLE_ANSWER
    right = MAXIMUM_POSSIBLE_ANSWER
    while left <= right:
        mid = (left + right) // 2
        if check(mid):
            left = mid + 1
        else:
            right = mid - 1
    
    return right

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0e3u1v/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


### 回溯

```cpp
int backtrack(STATE curr, OTHER_ARGUMENTS...) {
    if (BASE_CASE) {
        // 修改答案
        return 0;
    }

    int ans = 0;
    for (ITERATE_OVER_INPUT) {
        // 修改当前状态
        ans += backtrack(curr, OTHER_ARGUMENTS...)
        // 撤消对当前状态的修改
    }

    return ans;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0eq7sj/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```python
def backtrack(curr, OTHER_ARGUMENTS...):
    if (BASE_CASE):
        # 修改答案
        return
    
    ans = 0
    for (ITERATE_OVER_INPUT):
        # 修改当前状态
        ans += backtrack(curr, OTHER_ARGUMENTS...)
        # 撤消对当前状态的修改
    
    return ans

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0eq7sj/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


### 动态规划: 自顶向下法

```cpp
unordered_map<STATE, int> memo;

int fn(vector<int>& arr) {
    return dp(STATE_FOR_WHOLE_INPUT, arr);
}

int dp(STATE, vector<int>& arr) {
    if (BASE_CASE) {
        return 0;
    }

    if (memo.find(STATE) != memo.end()) {
        return memo[STATE];
    }

    int ans = RECURRENCE_RELATION(STATE);
    memo[STATE] = ans;
    return ans;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0e6wzt/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


```py
def fn(arr):
    def dp(STATE):
        if BASE_CASE:
            return 0
        
        if STATE in memo:
            return memo[STATE]
        
        ans = RECURRENCE_RELATION(STATE)
        memo[STATE] = ans
        return ans

    memo = {}
    return dp(STATE_FOR_WHOLE_INPUT)

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0e6wzt/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


### 构建前缀树（字典树）

```cpp
// 注意:只有需要在每个节点上存储数据时才需要使用类。
// 否则，您可以只使用哈希映射实现一个前缀树。
struct TrieNode {
    int data;
    unordered_map<char, TrieNode*> children;
    TrieNode() : data(0), children(unordered_map<char, TrieNode*>()) {}
};

TrieNode* buildTrie(vector<string> words) {
    TrieNode* root = new TrieNode();
    for (string word: words) {
        TrieNode* curr = root;
        for (char c: word) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];
            // 这个位置上的 curr 已经有一个完整的单词
            // 如果你愿意，你可以在这里执行更多的操作来给 curr 添加属性
        }
    }

    return root;
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0ek2gr/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

```py
# 注意:只有需要在每个节点上存储数据时才需要使用类。
# 否则，您可以只使用哈希映射实现一个前缀树。
class TrieNode:
    def __init__(self):
        # you can store data at nodes if you wish
        self.data = None
        self.children = {}

def fn(words):
    root = TrieNode()
    for word in words:
        curr = root
        for c in word:
            if c not in curr.children:
                curr.children[c] = TrieNode()
            curr = curr.children[c]
        # 这个位置上的 curr 已经有一个完整的单词
        # 如果你愿意，你可以在这里执行更多的操作来给 curr 添加属性
    
    return root

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/arithmetic-interview-cheat-sheet/0ek2gr/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


## 算法面试详解


### 介绍

在面试开始时，大多数情况下面试官会简单介绍自己和他们在公司的角色，然后让你做自我介绍。

准备并排练一段自我介绍。自我介绍应该在 30 秒内总结你的教育背景、工作经历和兴趣爱好。
保持微笑，且让说话的声音听起来自信。
当面试官谈论他们在公司的工作时，请注意听 - 这有助于稍后提出相关问题。
如果面试官提到任何你也感兴趣的事情，无论是他们的工作还是爱好，提出来。

### 问题陈述


在自我介绍之后，面试官会给你一个问题陈述。如果您在共享文本编辑器中答题，他们很可能将问题描述和测试用例一起粘贴到编辑器中，然后将问题读给您听。

确保你完全理解了这个问题。在面试官把问题读完之后，通过将其解释回给他们来确认问题在问什么。

询问有关输入的问题阐述，例如:

输入是只有整数，还是可以有其他类型？
我能假设输入是有序的吗？
输入是保证有元素还是可以为空？
如果给出了无效输入，我该如何处理？
询问预期的输入大小。有时候，面试官会含糊其辞，但如果他们确实给了你一个范围，这可能是一个线索。例如，如果 n 非常小，则可能是回溯。如果 n 在 100 - 1000 左右，O(n^2) 的解决方案可能是最优的。 如果 n 非常大, 那么你可以需要比 O(n) 更好的解决方案。

提出明确的问题不仅能帮助你更好地理解问题，还能表现出对细节的关注，以及对边缘情况的考虑。

### 头脑风暴 DS&A

尝试找出适用的数据结构或算法。分解问题并尝试找到你会的常用解法。弄清楚问题需要你做什么，并考虑什么样的数据结构或算法可以以较好的时间复杂度来完成。

把你的想法都说出来。这会让面试官知道你善于权衡利弊。如果问题涉及到查看子数组，那么应该考虑滑动窗口，因为每个窗口都代表一个子数组。即使你错了，面试官仍然会欣赏你的思考过程。

通过把想法都说出来，面试官也可以借此给你提示，并为你指出正确的方向。

一旦决定了要使用的数据结构/算法，现在就需要构造实际的算法。在编码之前，你应该考虑算法的大致步骤，向面试官解释这些步骤，并确保他们理解并同意这是一个合理的方法。通常，如果你走错了路，他们会巧妙地暗示你。

在这个阶段你能接受面试官所说的话是 非常 重要的。请记住：他们知道最佳解决方案。如果他们给你提示，那是因为他们希望你成功。不要固执，准备好探索他们给你的想法。

### 实操



一旦你想出了一个算法，并让面试官同意了，就该开始写代码了。

如果你打算使用一个库或模块，例如 Python 的集合，在开始之前确保面试官可以接受。
当你写代码时，解释你的决策。例如，如果你正在解决一个图形问题，当你声明一个集合 seen，解释它是为了防止访问同一个节点超过一次，从而也防止了循环。
编写干净的代码。每一种主流的编程语言都有一个关于代码应该如何编写的约定。确保你知道你打算使用的语言的基础知识。Google 提供了适用于所有主流语言的 [google code style 总结](https://google.github.io/styleguide/)。最重要的部分是大小写约定、缩进、空格和全局变量。
避免重复代码。例如，如果您在网格上进行 DFS 操作，则应该反复使用方向数组 [(0, 1), (1, 0), (0, -1), (-1, 0)] ，而不是为每个方向编写相同的逻辑 4 次。如果你发现自己在多个地方编写类似的代码，可以考虑创建一个函数或使用循环来简化它。
不要害怕使用辅助函数。它们使你的代码更加模块化，这在实际软件工程中非常重要。之后的代码说不定还会用上辅助函数。
如果你遇到困难或意识到你最初的计划可能行不通，不要慌。与面试官交流你的疑虑。如果你默默地挣扎，很可能又会钻牛角尖。

一种策略是首先实现一个暴力解决方案，同时承认 这是一个次优解决方案。完成后，分析算法的每个部分，找出哪些步骤 “慢”，并尝试思考如何加快速度。让面试官参与进来，让他们参与讨论 —— 他们通常愿意提供帮助。


### 测试 & debug


一旦你写完代码，你的面试官可能会想要测试你的代码。根据公司的不同，会有一些不同的环境:

内置测试用例，代码需要运行

这些平台类似于 LeetCode。将会有各种各样的测试用例 —— 小输入，大输入，测试边缘用例的输入。
这种环境给您的代码带来了最大的压力，因为会暴露出不完美的解决方案。
但是，它也为创建您自己的测试带来了最小的压力，因为测试用例已经内置在了内部。
自己写测试用例，代码需要运行

这些平台通常是支持运行代码的共享文本编辑器。面试官会希望你编写自己的测试用例。
要真正测试代码，你应该在代码的最外层范围编写，即代码将首先运行的地方。假设你在函数中解决了问题 (就像在 LeetCode 上)，你可以用你编写的测试用例调用你的函数，并将结果打印到控制台。
在编写自己的测试时，请确保尝试各种测试。包括边缘情况、直觉输入和可能无效的输入 (如果面试官想让你处理这种情况)。
自己写测试用例，代码不需要运行

这些平台只是共享文本编辑器，不支持运行代码。面试官会希望你编写自己的测试用例，并且手动模拟运行。
为了 “测试” 代码，你必须在每个测试用例中手动检查算法。试着压缩一些琐碎的部分 —— 例如，你正在创建一个前缀和，不要 字面上 遍历每个元素的 for 循环。可以这样说:“在这个 for 循环之后，我们将有一个前缀和，他是这样的……”。
在遍历代码时，将函数中使用的变量写入 (在编辑器中，函数外部的某处)，并不断更新它们。
不管在什么情况下，如果您的代码出现了错误，不要慌!如果环境支持运行代码，请在相关位置放置打印语句以尝试识别问题。用一个小的测试用例手动遍历(就像你没有运行环境时所做的那样)。当你这样做的时候，讨论变量的期望值应该是什么，并将它们与实际值进行比较。再说一遍，你说话越多，面试官就越容易帮助你。

### 解释与跟进

在编写算法并运行测试用例之后，准备回答关于算法的问题。你应该准备好回答的问题包括:

算法的时间和空间复杂度是多少？
你应该从最坏的情况来考虑。但是，如果最坏的情况很少，并且平均情况的运行时明显更快，那么你还应该提到这一点。
你为什么选择……？
这可以是你对数据结构的选择，算法的选择，循环配置的选择。准备好解释你的思考过程。
你认为算法在时间和空间复杂度上是否可以改进？
如果问题需要遍历输入中的每个元素 (假设输入没有排序，需要找到最大的元素)，那么你很可能无法比 O(n) 更快。否则你很可能无法比 O(logn) 更快。
如果面试官问这个问题，答案 通常 是肯定的。在断言你的算法是最优的时候要小心 —— 不要轻易使用绝对的形容。
如果面试还有剩余时间，你可能会被问到一个全新的问题。在这种情况下，从步骤 2（问题陈述）重新开始。但是，你也可能会被要求对你已经解决的问题进行跟进。面试官可能会引入新的约束，要求改进空间复杂度，或任何其他数量的东西。

这部分是为什么真正理解解决方案而不是仅仅记住它们很重要的原因。

### 结尾


面试官通常会在面试结束时留出几分钟的时间让你问一些关于他们或公司的问题。在这一点上，很少能改善面试的结果，但你肯定能让它变得更糟。

面试是双向的。你应该利用这段时间来了解这家公司，看看你是否愿意在那里工作。你应该在面试前准备一些问题，比如:

在公司的一天中会做些什么？
你为什么决定加入这家公司而不是另一家公司？
关于这份工作，你最喜欢和最不喜欢的是什么？
我可以从事什么样的工作？
所有的大公司都会有自己的科技博客。展示你对这家公司感兴趣的一个好方法是阅读一些博客文章，并编制一个关于公司为什么做出这些决定的问题清单。

保持兴趣，保持微笑，倾听面试官的回答，并提出后续问题，以表明你理解他们的答案。

如果你没有高质量的问题，或者表现得无聊或不感兴趣，这可能会给面试官一个不好的信号。如果面试官最后不喜欢你，你在技术方面做得再好也没用。

### 面试备考总览


以下是「面试的阶段」一文的摘要。如果您进行远程面试，您可以打印此浓缩版并在面试期间将其放在您面前。

第一阶段：介绍

30-60 秒介绍您的教育、工作经验和兴趣。
自信，保持微笑。
当面试官谈论他们自己时要注意，稍后将他们的工作纳入您的问题。
第二阶段：问题陈述

在面试官将问题读给你听后，将问题复述给他们。
询问有关输入的问题描述，例如预期的输入大小、边缘情况和无效输入。
第三阶段：头脑风暴 DS&A

把你所有的想法都说出来。
分解问题：弄清楚你需要做什么，并思考什么数据结构或算法可以以良好的时间复杂度完成它。
接受面试官的任何评论或反馈，他们可能试图暗示您找到正确的解决方案。
一旦你有了想法，在编码之前，向面试官解释你的想法，并确保他们理解并同意这是一种合理的方法。
第四阶段：实操

在你实际编码时解释你的决策。当你声明集合之类的东西时，解释一下目的是什么。
编写符合规范编程语言约定的代码。
避免编写重复代码 - 如果你多次编写类似代码，请使用辅助函数或 for 循环。
如果你被卡住了，不要惊慌 - 与你的面试官交流你的疑虑。
不要害怕暴力解决方案（同时承认它是暴力解法），然后通过优化 “慢” 的部分来改进它。
继续把你的想法说出来并与面试官交谈。这让他们更容易给你提示。
第五阶段：测试 & debug

遍历测试用例时，通过在文件底部写入来跟踪变量，并不断更新它们。压缩琐碎的部分，例如创建前缀和以节省时间。
如果有错误并且环境支持运行代码，将打印语句放入你的算法并遍历一个小测试用例，比较变量的预期值和实际值。
如果遇到任何问题，请直接说出问题并继续与面试官交谈。
第六阶段：解释和跟进

您应该准备回答的问题：

时间和空间复杂度，平均和最坏情况。
你为什么选择这个数据结构、算法或逻辑？
您认为该算法可以在复杂性方面进行改进吗？如果他们问你这个问题，那么答案通常是，特别是如果你的算法比 O(n) 慢。
第七阶段：结尾

准备好有关公司的问题。
对面试官的回答表现出感兴趣、微笑并提出后续问题。
























# 排序算法


在不同领域，排序算法的实现各有千秋。总体来看，排序算法大致可分为十类：

选泡插：选择排序、冒泡排序、插入排序
快归希堆：快速排序、归并排序、希尔排序、堆排序
桶计基：桶排序、计数排序、基数排序
虽然工作中很少需要我们手打排序算法，只需要调用基础库中的 Arrays.sort() 便可解决排序问题。但你可曾静下心来，阅读 Arrays.sort() 背后的原理，它是采用了哪种排序算法呢？

事实上，Arrays.sort() 函数并没有采用单一的排序算法。Java 中的 Arrays.sort() 函数是由 Java 语言的几位创始人编写的，这个小小的函数逻辑严密，并且每个步骤都被精心设计，为了最大化性能做了一层又一层的优化，根据数据的概况采用双轴快排、归并或二分插入算法完成排序，堪称工业级排序算法的典范，理清之后其乐无穷。

并且，排序算法深受面试官的喜爱，在人才招聘时，总是将排序算法作为程序员的基本功来考察。对排序算法的理解深度在一定程度上反映了程序员逻辑思维的严谨度。攻克排序算法的难关是每位程序大牛的必经之路。

如牛顿所言，正是站在巨人的肩膀上，我们才能望得更远。本系列文章我们就来一起梳理一下排序算法的前世今生。

##  O(n^2) 级排序算法

### 冒泡排序

冒泡排序是入门级的算法，但也有一些有趣的玩法。通常来说，冒泡排序有三种写法：

一边比较一边向后两两交换，将最大值 / 最小值冒泡到最后一位；
经过优化的写法：使用一个变量记录当前轮次的比较是否发生过交换，如果没有发生交换表示已经有序，不再继续排序；
进一步优化的写法：除了使用变量记录当前轮次是否发生交换外，再使用一个变量记录上次发生交换的位置，下一轮排序时到达上次交换的位置就停止比较。

first method

```java
public static void bubbleSort(int[] arr) {
    for (int i = 0; i < arr.length - 1; i++) {
        for (int j = 0; j < arr.length - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // 如果左边的数大于右边的数，则交换，保证右边的数字最大
                swap(arr, j, j + 1);
            }
        }
    }
}
// 交换元素
private static void swap(int[] arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


```

second method

```java
public static void bubbleSort(int[] arr) {
    // 记录每轮冒泡是否发生了交换
    boolean swapped;
    for (int i = 0; i < arr.length - 1; i++) {
        swapped = false;
        for (int j = 0; j < arr.length - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
                swapped = true;
            }
        }
        // 如果没有发生过交换，直接退出循环
        if (!swapped) break;
    }
}


```

third method

```java

public static void bubbleSort(int[] arr) {
    boolean swapped = true;
    // 最后一个没有经过排序的元素的下标
    int indexOfLastUnsortedElement = arr.length - 1;
    // 上次发生交换的位置
    int swappedIndex = -1;
    while (swapped) {
        swapped = false;
        for (int i = 0; i < indexOfLastUnsortedElement; i++) {
            if (arr[i] > arr[i + 1]) {
                // 如果左边的数大于右边的数，则交换，保证右边的数字最大
                swap(arr, i, i + 1);
                // 表示发生了交换
                swapped = true;
                // 更新交换的位置
                swappedIndex = i;
            }
        }
        // 最后一个没有经过排序的元素的下标就是最后一次发生交换的位置
        indexOfLastUnsortedElement = swappedIndex;
    }
}
// 交换元素
private static void swap(int[] arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


```

经过再一次的优化，代码看起来就稍微有点复杂了。最外层的 while 循环每经过一轮，剩余数字中的最大值仍然是被移动到当前轮次的最后一位。

在下一轮比较时，只需比较到上一轮比较中，最后一次发生交换的位置即可。因为后面的所有元素都没有发生过交换，必然已经有序了。

当一轮比较中从头到尾都没有发生过交换，则表示整个列表已经有序，排序完成。



通过位运算完成数字交换
```c
a = a ^ b;
b = b ^ a;
a = a ^ b;
```

### 选择排序


选择排序的思想是：双重循环遍历数组，每经过一轮比较，找到最小元素的下标，将其交换至首位。

```java
public static void selectionSort(int[] arr) {
    int minIndex;
    for (int i = 0; i < arr.length - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < arr.length; j++) {
            if (arr[minIndex] > arr[j]) {
                // 记录最小值的下标
                minIndex = j;
            }
        }
        // 将最小元素交换至首位
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}


```

相同点：

都是两层循环，时间复杂度都为 n^2 都只使用有限个变量，空间复杂度 O(1)。
不同点：

冒泡排序在比较过程中就不断交换；而选择排序增加了一个变量保存最小值 / 最大值的下标，遍历完成后才交换，减少了交换次数。
事实上，冒泡排序和选择排序还有一个非常重要的不同点，那就是：

冒泡排序法是稳定的，选择排序法是不稳定的。

### 插入排序


插入排序有两种写法：

交换法：在新数字插入过程中，不断与前面的数字交换，直到找到自己合适的位置。
移动法：在新数字插入过程中，与前面的数字不断比较，前面的数字不断向后挪出位置，当新数字找到自己的位置后，插入一次即可。

```java
public static void insertSort(int[] arr) {
    // 从第二个数开始，往前插入数字
    for (int i = 1; i < arr.length; i++) {
        // j 记录当前数字下标
        int j = i;
        // 当前数字比前一个数字小，则将当前数字与前一个数字交换
        while (j >= 1 && arr[j] < arr[j - 1]) {
            swap(arr, j, j - 1);
            // 更新当前数字下标
            j--;
        }
    }
}
private static void swap(int[] arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


```

移动法插入排序
我们发现，在交换法插入排序中，每次交换数字时，swap 函数都会进行三次赋值操作。但实际上，新插入的这个数字并不一定适合与它交换的数字所在的位置。也就是说，它刚换到新的位置上不久，下一次比较后，如果又需要交换，它马上又会被换到前一个数字的位置。

由此，我们可以想到一种优化方案：让新插入的数字先进行比较，前面比它大的数字不断向后移动，直到找到适合这个新数字的位置后，新数字只做一次插入操作即可。

这种方案我们需要把新插入的数字暂存起来，代码如下：


```java
public static void insertSort(int[] arr) {
    // 从第二个数开始，往前插入数字
    for (int i = 1; i < arr.length; i++) {
        int currentNumber = arr[i];
        int j = i - 1;
        // 寻找插入位置的过程中，不断地将比 currentNumber 大的数字向后挪
        while (j >= 0 && currentNumber < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        // 两种情况会跳出循环：1. 遇到一个小于或等于 currentNumber 的数字，跳出循环，currentNumber 就坐到它后面。
        // 2. 已经走到数列头部，仍然没有遇到小于或等于 currentNumber 的数字，也会跳出循环，此时 j 等于 -1，currentNumber 就坐到数列头部。
        arr[j + 1] = currentNumber;
    }
}


```


### sum

冒泡排序
冒泡排序有两种优化方式：

记录当前轮次是否发生过交换，没有发生过交换表示数组已经有序；
记录上次发生交换的位置，下一轮排序时只比较到此位置。
选择排序
选择排序可以演变为二元选择排序：

二元选择排序：一次遍历选出两个值——最大值和最小值；
二元选择排序剪枝优化：当某一轮遍历出现最大值和最小值相等，表示数组中剩余元素已经全部相等。
插入排序
插入排序有两种写法：

交换法：新数字通过不断交换找到自己合适的位置；
移动法：旧数字不断向后移动，直到新数字找到合适的位置。
相同点
时间复杂度都是 O(n^2) ，空间复杂度都是 O(1)。

都需要采用两重循环。

不同点
选择排序是不稳定的，冒泡排序、插入排序是稳定的；
在这三个排序算法中，选择排序交换的次数是最少的；
在数组几乎有序的情况下，插入排序的时间复杂度接近线性级别。


## O(nlogn) 级排序算法

### 希尔排序

![alt text](image-45.png)

![shell sort](./1643081683-ORhiPp-希尔排序.gif)


![alt text](image-46.png)


```java
public static void shellSort(int[] arr) {
    // 间隔序列，在希尔排序中我们称之为增量序列
    for (int gap = arr.length / 2; gap > 0; gap /= 2) {
        // 分组
        for (int groupStartIndex = 0; groupStartIndex < gap; groupStartIndex++) {
            // 插入排序
            for (int currentIndex = groupStartIndex + gap; currentIndex < arr.length; currentIndex += gap) {
                // currentNumber 站起来，开始找位置
                int currentNumber = arr[currentIndex];
                int preIndex = currentIndex - gap;
                while (preIndex >= groupStartIndex && currentNumber < arr[preIndex]) {
                    // 向后挪位置
                    arr[preIndex + gap] = arr[preIndex];
                    preIndex -= gap;
                }
                // currentNumber 找到了自己的位置，坐下
                arr[preIndex + gap] = currentNumber;
            }
        }
    }
}


```

注：由于希尔排序理解起来有一定的难度，所以笔者采用了更准确的命名方式替代 i、j 等变量名。

这份代码与我们上文中提到的思路是一模一样的，先分组，再对每组进行插入排序。同样地，这里的插入排序也可以采用交换元素的方式。

实际上，这段代码可以优化一下。我们现在的处理方式是：处理完一组间隔序列后，再回来处理下一组间隔序列，这非常符合人类思维。但对于计算机来说，它更喜欢从第 gap 个元素开始，按照顺序将每个元素依次向前插入自己所在的组这种方式。虽然这个过程看起来是在不同的间隔序列中不断跳跃，但站在计算机的角度，它是在访问一段连续数组。

```java
public static void shellSort(int[] arr) {
    // 间隔序列，在希尔排序中我们称之为增量序列
    for (int gap = arr.length / 2; gap > 0; gap /= 2) {
        // 从 gap 开始，按照顺序将每个元素依次向前插入自己所在的组
        for (int i = gap; i < arr.length; i++) {
            // currentNumber 站起来，开始找位置
            int currentNumber = arr[i];
            // 该组前一个数字的索引
            int preIndex = i - gap;
            while (preIndex >= 0 && currentNumber < arr[preIndex]) {
                // 向后挪位置
                arr[preIndex + gap] = arr[preIndex];
                preIndex -= gap;
            }
            // currentNumber 找到了自己的位置，坐下
            arr[preIndex + gap] = currentNumber;
        }
    }
}


```


经过优化之后，这段代码看起来就和插入排序非常相似了，区别仅在于希尔排序最外层嵌套了一个缩小增量的 for 循环；并且插入时不再是相邻数字挪动，而是以增量为步长挪动

![alt text](image-47.png)

```java
public static void shellSortByKnuth(int[] arr) {
    // 找到当前数组需要用到的 Knuth 序列中的最大值
    int maxKnuthNumber = 1;
    while (maxKnuthNumber <= arr.length / 3) {
        maxKnuthNumber = maxKnuthNumber * 3 + 1;
    }
    // 增量按照 Knuth 序列规则依次递减
    for (int gap = maxKnuthNumber; gap > 0; gap = (gap - 1) / 3) {
        // 从 gap 开始，按照顺序将每个元素依次向前插入自己所在的组
        for (int i = gap; i < arr.length; i++) {
            // currentNumber 站起来，开始找位置
            int currentNumber = arr[i];
            // 该组前一个数字的索引
            int preIndex = i - gap;
            while (preIndex >= 0 && currentNumber < arr[preIndex]) {
                // 向后挪位置
                arr[preIndex + gap] = arr[preIndex];
                preIndex -= gap;
            }
            // currentNumber 找到了自己的位置，坐下
            arr[preIndex + gap] = currentNumber;
        }
    }
}


```


![alt text](image-48.png)


虽然插入排序是稳定的排序算法，但希尔排序是不稳定的。在增量较大时，排序过程可能会破坏原有数组中相同关键字的相对次序。

![alt text](image-49.png)


### 堆排序

数组、链表都是一维的数据结构，相对来说比较容易理解，而堆是二维的数据结构，对抽象思维的要求更高，所以许多程序员「谈堆色变」。但堆又是数据结构进阶必经的一步，我们不妨静下心来，将其梳理清楚。

![alt text](image-50.png)

![alt text](image-51.png)

![alt text](./912_fig2.gif)

![alt text](./912_fig3.gif)


完全二叉树的性质

1. 完全二叉树是一个高度为 h 的二叉树，除了最后一层外，其他层的节点数都达到最大值，最后一层的节点都集中在最左边。
2. 完全二叉树的节点总数 n 满足：2^h - 1 <= n <= 2^(h+1) - 1。
3. 完全二叉树的叶子节点都在最后两层，且最后一层的叶子节点都集中在最左边。

![alt text](image-52.png)


```java
public static void heapSort(int[] arr) {
    // 构建初始大顶堆
    buildMaxHeap(arr);
    for (int i = arr.length - 1; i > 0; i--) {
        // 将最大值交换到数组最后
        swap(arr, 0, i);
        // 调整剩余数组，使其满足大顶堆
        maxHeapify(arr, 0, i);
    }
}
// 构建初始大顶堆
private static void buildMaxHeap(int[] arr) {
    // 从最后一个非叶子结点开始调整大顶堆，最后一个非叶子结点的下标就是 arr.length / 2-1
    for (int i = arr.length / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, i, arr.length);
    }
}
// 调整大顶堆，第三个参数表示剩余未排序的数字的数量，也就是剩余堆的大小
private static void maxHeapify(int[] arr, int i, int heapSize) {
    // 左子结点下标
    int l = 2 * i + 1;
    // 右子结点下标
    int r = l + 1;
    // 记录根结点、左子树结点、右子树结点三者中的最大值下标
    int largest = i;
    // 与左子树结点比较
    if (l < heapSize && arr[l] > arr[largest]) {
        largest = l;
    }
    // 与右子树结点比较
    if (r < heapSize && arr[r] > arr[largest]) {
        largest = r;
    }
    if (largest != i) {
        // 将最大值交换为根结点
        swap(arr, i, largest);
        // 再次调整交换数字后的大顶堆
        maxHeapify(arr, largest, heapSize);
    }
}
private static void swap(int[] arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


```

![alt text](image-53.png)


![alt text](image-54.png)

![alt text](image-55.png)


### 快速排序

![alt text](image-56.png)

```java
public static void quickSort(int[] arr) {
    quickSort(arr, 0, arr.length - 1);
}
public static void quickSort(int[] arr, int start, int end) {
    // 将数组分区，并获得中间值的下标
    int middle = partition(arr, start, end);
    // 对左边区域快速排序
    quickSort(arr, start, middle - 1);
    // 对右边区域快速排序
    quickSort(arr, middle + 1, end);
}
public static int partition(int[] arr, int start, int end) {
    // TODO: 将 arr 从 start 到 end 分区，左边区域比基数小，右边区域比基数大，然后返回中间值的下标
}


```

![alt text](image-57.png)


```java
public static void quickSort(int[] arr, int start, int end) {
    // 将数组分区，并获得中间值的下标
    int middle = partition(arr, start, end);
    // 当左边区域中至少有 2 个数字时，对左边区域快速排序
    if (start != middle && start != middle - 1) quickSort(arr, start, middle - 1);
    // 当右边区域中至少有 2 个数字时，对右边区域快速排序
    if (middle != end && middle != end - 1) quickSort(arr, middle + 1, end);
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/sort-algorithms/eul7hm/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

![alt text](image-58.png)


```java
public static void quickSort(int[] arr, int start, int end) {
    // 如果区域内的数字少于 2 个，退出递归
    if (start == end || start == end + 1) return;
    // 将数组分区，并获得中间值的下标
    int middle = partition(arr, start, end);
    // 对左边区域快速排序
    quickSort(arr, start, middle - 1);
    // 对右边区域快速排序
    quickSort(arr, middle + 1, end);
}

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/sort-algorithms/eul7hm/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```




































































