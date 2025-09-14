
# 动态规划：线性 & 区间动态

理解动态规划的基本思想
了解动态规划算法的优缺点和问题分类
掌握运用动态规划解决问题的思路
能够运用动态规划解决线性、前缀和、区间这三类问题


## 简介

![Alt text](image.png)

![Alt text](image-1.png)


![Alt text](image-2.png)


![Alt text](image-3.png)

![Alt text](image-4.png)


![Alt text](image-5.png)

![Alt text](image-6.png)


## 线性动态规划


![Alt text](image-7.png)

![Alt text](image-8.png)


### 单串

![Alt text](image-9.png)

![Alt text](image-10.png)

![Alt text](image-11.png)
![Alt text](image-12.png)

![Alt text](image-13.png)
![Alt text](image-14.png)
![Alt text](image-15.png)


### 带维度单串 dp[i][k]

![Alt text](image-16.png)
![Alt text](image-17.png)
![Alt text](image-18.png)

### 双串

![Alt text](image-19.png)
![Alt text](image-20.png)
![Alt text](image-21.png)
![Alt text](image-22.png)
![Alt text](image-23.png)


### 矩阵

![Alt text](image-24.png)
![Alt text](image-25.png)
矩阵相关练习题
矩阵 dp[i][j]
矩阵 dp[i][j][k]


线性动态规划是动态规划中最基础的一类，它的状态一般物理意义很明确，易于分析。在初学动态规划时，通过线性动态规划的大量练习，可以不断加深动态规划的概念理解，例如动态规划中最重要的三个概念：最优子结构，重复子问题，无后效性。下面对动态规划的三个基本概念做个简要回顾，在线性动态规划的题目练习中可以不断地加深理解，之后再学习其它的动态规划类型就会容易很多。

最优子结构：如果问题的最优解所包含的子问题的解也是最优的，就称该问题具有最优子结构。
无后效性：即某阶段状态一旦确定，就不受这个状态以后决策的影响。也就是说，某状态以后的过程不会影响以前的状态，只与当前状态有关。
重复子问题：即子问题之间是不独立的，一个子问题在下一阶段决策中可能被多次使用到。（该性质并不是动态规划适用的必要条件，但是如果没有这条性质，动态规划算法同其他算法相比就不具备优势）
线性动态规划是动态规划中变化最多的一类。

首先线性动态规划针对的问题是最常见的数组，字符串，矩阵等，这三种数据结构本身就是线性的，因此出现这些类型的输入的时候，如果要用到动态规划，首先考虑线性动态规划就很合理了，因此很多问题不论最后正解是不是线性动态规划，都会首先想一下线性动态规划是否可行。

其次由于大部分问题的数据都是以这三种形式给出的，因此题目的变化会非常多，很多常见的输入形式以及问题都非常经典，都存在经典的状态设计。因此不考虑一些比较 Trick 的解法，仅仅是经典问题的经典状态设计，就比其它种类的动态规划问题多很多了。

例如单个数组或字符串上设计一维状态，两个数组或字符串上设计两维状态，以及矩阵上设计两维状态等等，同时以上三种情况的状态设计都有可能再加上额外的指标的状态，就是前面例题中的 k，这里面变化就很多了，比如有的题目在 k 这一维上要使用二分，贪心的策略，有的题目需要 DP 状态与数据结构配合来解决问题。

除此之外还有一类问题没有显式的数组，字符串，但是在求解的时候依然满足前面提到的动态规划三条基本概念，可以用动态规划求解，这种问题通常也是线性动态规划。如此多的变化仅仅本小节例举的题目是远远不够的，下一小节是线性动态规划的练习题，涉及到对线性动态规划的更多的变化。

## 前缀和

前缀和是一种查询数组中任意区间的元素的和的数据结构，这里数组给定之后就不变了。针对这个不变的数组，前缀和用于多次查询区间 [i, j] 上元素的和。

对于动态规划而言，前缀和的意义主要有两点：

一维和二维前缀和的推导，分别用到了单串和矩阵中最经典的状态设计以及状态转移；
在一些更复杂的动态规划问题中，状态转移的时候需要依赖区间和，因为状态转移是非常频繁的操作，因此必须高效地求区间和才能使得状态转移的时间复杂度可接受，此时就必须用到前缀和了。
除此之外，一些问题需要前缀和与其它数据结构配合来解决，也有两类：

先预处理出前缀和数组，这一步是动态规划，然后在前缀和数组上用其它数据结构解决；
还是按照动态规划的方式求前缀和，也需要额外的数据结构维护前缀和，但不是预处理好前缀和数组之后再用数据结构计算，而是每求出一个前缀和，就更新一次数据结构并维护答案。
前缀和的推导和计算隐含着动态规划的基本思想，同时它的状态设计是线性动态规划中比较简单的那一类。与线性动态规划一样，前缀和也有一维和二维两种场景。
虽然前缀和本身很简单，但需要用到它解决的问题非常多，与其它数据结构配合的变化也很多，因此需要从线性动态规划中剥离出来单独学习。

### 求区间和

![Alt text](image-26.png)

![Alt text](image-27.png)

![Alt text](image-28.png)

![Alt text](image-29.png)

### 数据结构维护前缀和

![Alt text](image-30.png)

![Alt text](image-31.png)

### 运算推广

![Alt text](image-32.png)


### 差分
![Alt text](image-33.png)


## 区间动态规划
在输入为长度为 n 的数组时，子问题用区间 [i..j] 表示。
状态的定义和转移都与区间有关，称为区间动态规划

![Alt text](image-34.png)

![Alt text](image-35.png)

![Alt text](image-36.png)

![Alt text](image-37.png)

![Alt text](image-38.png)

![Alt text](image-39.png)

![Alt text](image-40.png)

# 动态规划：状压、计数 & 数位动态

## 背包动态规划
![Alt text](image-41.png)


![Alt text](image-42.png)
![Alt text](image-43.png)
![Alt text](image-44.png)
![Alt text](image-45.png)
![Alt text](image-46.png)
![Alt text](image-47.png)
## 状态压缩动态规划

状态压缩动态规划是一类非常典型的动态规划，通常使用在 NP 问题的小规模求解中，虽然是指数级别的复杂度，但速度比搜索快。

![Alt text](image-48.png)
![Alt text](image-49.png)
![Alt text](image-50.png)
![Alt text](image-51.png)

## 计数问题

动态规划中的计数型问题就是利用动态规划的算法思想去计算出解决这个问题有多少种方法。
比如，从起点走到终点，可以有多少条路径，注意，是多少条，而不是具体路线的描述。
当然也有具体每一条路线的问法，这是 dfs 的问题了。

![Alt text](image-52.png)
![Alt text](image-53.png)
![Alt text](image-54.png)
计数问题相关练习题
路径问题
卡特兰数
铺砖问题
斐波那契
隐晦的递推关系


## 矩阵快速幂
是一种基础算法，本身与动态规划没有关系，但它可以用于优化线性递推关系的计算，并且其思路比较固定，因此在计数问题章节之后，在本章将矩阵快速幂做基础介绍。

![Alt text](image-55.png)

![Alt text](image-56.png)
![Alt text](image-57.png)

```c
using ll = long long;
const int M = 2;

struct Ma
{
    int a[M][M];
    Ma()
    {
        memset(a, 0, sizeof(a));
    }

    void init() // 复位为单位阵
    {
        a[0][0] = a[1][1] = 1;
        a[0][1] = a[1][1] = 0;
    }

    Ma operator*(const Ma& B) const
    {
        Ma ans;
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                for(int k = 0; k < M; ++k)
                    ans.a[i][j] += a[i][k] * B.a[k][j];
        return ans;
    }

    Ma operator^(int n) const
    {
        Ma ans;
        ans.init();
        Ma A = *this; // 拷贝一个出来用于自乘
        while(n)
        {
            if(n & 1)
                ans = ans * A;
            A = A * A;
            n >>= 1;
        }
        return ans;
    }
};


```
![Alt text](image-58.png)
在上一章中的 16 道练习题中，部分题目的递推关系是线性的，进而可以用矩阵快速幂来做，尝试判断哪些题目可以用矩阵快速幂做，并用矩阵快速幂解决这些问题，加深对本节的理解。

## 数位 DP 
在基础的动态规划问题当中算是比较难的一类，因为数位 DP 的状态的物理意义不太好理解。其它的动态规划，比如区间 DP 状态的物理意义就是区间，状态压缩 DP 中状态的物理意义就是集合，这都比较好理解。

但是数位 DP 比其它 DP 好的一面是数位 DP 的思维相对比较固定。 一个是解决的问题模式比较固定，一个是状态设计也比较固定，因此可以通过一些常见问题把数位 DP 的套路了解个大概。

力扣上有几道数位 DP 的题目，通过这些题目我们可以大致了解数位 DP 的思考过程和做法。

![Alt text](image-59.png)
![Alt text](image-60.png)
![Alt text](image-61.png)
```cpp
int getdp(int pos, int lim, const vector<int>& digits, const set<int>& num_set, vector<vector<int>>& dp)
{
    if(pos == -1) return 1;
    if(dp[pos][lim] != -1)
        return dp[pos][lim];
    dp[pos][lim] = 0;
    int up = lim ? digits[pos] : 9; // 当前要枚举到的上界
    for(int i: num_set) // 枚举当前位所有可能数字
    {
        if(i > up)
            break;
        dp[pos][lim] += getdp(pos - 1, lim && i == up, digits, num_set, dp); // 本位被限制且选顶到上界的数字,下一位才被限制
    }
    return dp[pos][lim];
}


```
前导零的分析
增加 zero 状态, 表示高位是否是前导零。

如果高位选了前导零，则当前位无限制，且还可以选前导零。
如果高位没有选前导零且未顶到上界，则当前位在可选数字集合的范围内无限制。
如果高位顶到了上界，则当前位的选择被限制。
力扣上数位 DP 的题目不多，下一节提供了 9 道练习题，可以巩固数位 DP 的思维方式。

# 动态规划：树形、图上、概率 & 博弈动态

## 1 2期回顾
![Alt text](image-62.png)

![Alt text](image-63.png)

![Alt text](image-64.png)

「单串 DP」
对于「单串线性 DP」问题，i 是单串 s 上的位置。作为阶段具有时间或者位置等含义。有时只有单串上的位置不足以表示状态，需要同时附加一个维度 k，一般 k 有长度、个数、次数、颜色等含义。另，所附加的维度有时候可以是多个，如 k1, k2, ...

![Alt text](image-65.png)

![Alt text](image-66.png)

![Alt text](image-67.png)
![Alt text](image-68.png)
![Alt text](image-69.png)
![Alt text](image-70.png)

![Alt text](image-71.png)
![Alt text](image-72.png)
![Alt text](image-73.png)

本章我们介绍「线性 DP」中比较重要，同时在前两期没有详细介绍的两块内容，一个是最长上升子序列，一个是「棋盘 DP」。

在动态规划精讲第一期中，我们有介绍过最长上升子序列问题并用动态规划的方法进行解决。实际上最长上升子序列还有其它解法，以及力扣上有很多最长上升子序列的变种问题以及包装之后的问题。我们在这一小节进行介绍。

首先我们介绍最长上升子序列基于二分的解法，这是 LIS 问题的最好的解法，除此之外还有用线段树优化DP的方式的解法，这部分在动态规划精讲第四期关于DP的优化方法中介绍。

然后我们介绍最长上升子序列的变形问题，一个是最长上升子序列个数，一个是最长上升子串。

然后我们介绍一些力扣上的一些多维属性的最长上升子序列问题。

最后我门介绍需要自定义 LIS 中的小于的一些问题，这些问题只要能正确定义小于，就可以转换成最长上升子序列问题。



在动态规划精讲第一期中，我们有介绍过在矩阵上进行线性推导的动态规划问题，但是没有系统地介绍，本小节将这个知识点补充一下。

「棋盘 DP」是一种在矩阵上进行状态推导的动态规划问题。i, j 分别是棋盘(矩阵)的横纵坐标，但并不一定要共同作为阶段。阶段划分有两种情况都比较常见：

仅 i 作为阶段，具有位置等含义。同时 j 是附加状态。
i, j 共同作为阶段，具有位置等含义。没有附加维度。
这两种阶段划分方式的思路有区别，第一种是一行一行地考虑，第二种是一个位置一个位置地考虑。

## 树形动态规划
![Alt text](image-74.png)

![Alt text](image-75.png)
![Alt text](image-76.png)
![Alt text](image-77.png)
注意到在节点 u 时，状态转移过程只需要 dp[v][0]，而不需要 dp[v][1]，因此 dfs 仅返回 dp[v][0] 即可。

代码中 max1 表示 dp[u][0], max2 表示 dp[u][1]。

```cpp
class Solution {
public:
    int treeDiameter(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<vector<int> > g(n + 1);
        for(const auto &e: edges)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        int ans = 0;
        dfs(0, -1, g, ans);
        return ans;
    }

private:
    int dfs(int u, int fa, const vector<vector<int> >& g, int& ans)
    {
        int max1 = 0, max2 = 0;
        for(int v: g[u])
        {
            if(v != fa)
            {
                int t = dfs(v, u, g, ans) + 1;
                if(max1 < t)
                {
                    max2 = max1;
                    max1 = t;
                }
                else if(max2 < t)
                    max2 = t;
            }
        }
        ans = max(ans, (max1 + max2));
        return max1;
    }
};

```

![Alt text](image-78.png)
![Alt text](image-79.png)
![Alt text](image-80.png)
```cpp
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<vector<int> > g(n); // 邻接表
        for(vector<int> &edge: edges)
        {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        vector<int> dpdown(n, 0), dpup(n, 0);
        // 第一次DFS记录每个结点在作为子树根结点的最大高度。
        dfs_1(0, -1, dpdown, g);
        // 第二次DFS补全每个结点作为总根结点的最大高度，差距就在于需要统计上从父结点传递过来的子树分支。
        dfs_2(0, -1, dpdown, dpup, g);

        int min_ans = n;
        vector<int> ans;
        for(int i = 0; i < n; ++i)
        {
            if(min_ans > dpdown[i])
            {
                min_ans = dpdown[i];
                ans.clear();
                ans.push_back(i);
            }
            else if(min_ans == dpdown[i])
                ans.push_back(i);
        }
        return ans;
    }

private:
    void dfs_1(int u, int fa, vector<int>& dpdown, vector<vector<int> >& g)
    {
        dpdown[u] = 0;
        for(auto &v: g[u])
        {
            if(v == fa) continue;
            dfs_1(v, u, dpdown, g);
            dpdown[u] = max(dpdown[u], dpdown[v] + 1);
        }
    }

    void dfs_2(int u, int fa, vector<int>& dpdown, vector<int>& dpup, vector<vector<int> >& g)
    {
        dpdown[u] = max(dpdown[u], dpup[u]);
        int max_1 = 0, max_2 = 0; // 这里需要最大高度和次大高度
        for(auto &v: g[u])
        {
            if(v == fa) continue;
            if(max_1 < dpdown[v] + 1)
            {
                max_2 = max_1;
                max_1 = dpdown[v] + 1;
            }
            else if(max_2 < dpdown[v] + 1)
                max_2 = dpdown[v] + 1;
        }
        for(auto &v: g[u])
        {
            if(v == fa) continue;
            if (max_1 == dpdown[v] + 1) {
                // u 在 fa 的最长链上
                dpup[v] = max(dpup[u], max_2) + 1;
                dfs_2(v, u, dpdown, dpup, g);
            }
            else {
                dpup[v] = max(dpup[u], max_1) + 1;
                dfs_2(v, u, dpdown, dpup, g);
            }
        }
    }
};



```










