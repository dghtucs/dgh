#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    string A, B;
    cin >> A >> B;
    
    // 优化空间：使用一维数组，大小为较小的字符串长度+1，减少内存占用
    if (n < m) {
        swap(n, m);
        swap(A, B);
    }
    vector<int> dp(m + 1, 0);
    
    // 初始化边界条件（对应原代码中i=0的情况）
    for (int j = 0; j <= m; j++) {
        dp[j] = j;
    }
    
    // 填充dp数组（滚动更新）
    for (int i = 1; i <= n; i++) {
        int prev = dp[0]; // 保存上一行前一列的值（即dp[i-1][j-1]）
        dp[0] = i; // 当前行第0列的值（删除A的前i个字符）
        for (int j = 1; j <= m; j++) {
            int temp = dp[j]; // 暂存当前行更新前的dp[j]，作为下一轮的prev
            if (A[i-1] == B[j-1]) {
                dp[j] = prev; // 字符匹配，等价于dp[i-1][j-1]
            } else {
                // 取删除（dp[i-1][j]即当前dp[j]）或插入（dp[i][j-1]即更新后的dp[j-1]）的最小值+1
                dp[j] = min(dp[j], dp[j-1]) + 1;
            }
            prev = temp; // 更新prev为下一轮的dp[i-1][j-1]
        }
    }
    
    // 判断是否超过时间阈值
    if (dp[m] > k) {
        cout << -1 << endl;
    } else {
        cout << dp[m] << endl;
    }
    
    return 0;
}