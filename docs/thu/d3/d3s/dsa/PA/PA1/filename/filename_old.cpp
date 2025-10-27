#include <iostream>
#include <cstring>  
#include <string>
#include <cstdlib> 
#include <cmath>
using namespace std;
int k; // 允许的最大编辑距离
// 计算两个字符串的最长公共子序列（LCS）
int longestCommonSubsequence(const char* str1, const char* str2, int m, int n) {
    // 二维数组 dp，用于存储计算结果
    int dp[2][n + 1];
    memset(dp, 0, sizeof(dp)); // 初始化 dp 为 0
    // 遍历每个字符
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            // 检查当前字符位置是否在允许的范围内
            if (j - i > k)
                break; // 超过范围，退出循环
            if (i - j > k)
                j = i - k; // 调整 j 的值以保持在范围内
            else {
                // 如果两个字符相等，更新 dp 值
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i % 2][j] = dp[(i - 1) % 2][j - 1] + 1; // 递增 LCS 长度
                } else {
                    // 否则，取当前 LCS 的最大值
                    dp[i % 2][j] = max(dp[(i - 1) % 2][j], dp[i % 2][j - 1]);
                }
            }
        }
    }
   
    return dp[m % 2][n]; // 返回最终的 LCS 长度
}
int main() {
    // freopen("in.txt","r",stdin); 
    // freopen("out.txt","w",stdout);
    int n, m;
    scanf("%d %d %d", &m, &n, &k); // 从标准输入读取 m, n, k
    // 动态分配内存用于存储两个字符串
    const char* str1 = new char[m + 1]; 
    const char* str2 = new char[n + 1]; 
    scanf("%s", str1); 
    scanf("%s", str2); // 从标准输入读取 str2
    // 调用函数计算最长公共子序列
    int lcs = longestCommonSubsequence(str1, str2, m, n);
    // 计算字符串的不同字符数量
    int dis1 = strlen(str1) - lcs; // str1 的不同字符数量
    int dis2 = strlen(str2) - lcs; // str2 的不同字符数量
    // 计算总的字符差异
    int res = abs(dis1) + abs(dis2);
    if (res <= k) // 如果差异不超过允许的最大值
        printf("%d\n", res); // 输出差异
    else
        printf("%d\n", -1); // 否则输出 -1
    // 释放动态分配的内存
    delete[] str1; 
    delete[] str2; 

    return 0;
}
