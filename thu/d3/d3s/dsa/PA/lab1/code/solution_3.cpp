// solution_3.cpp
#include <cstdio>
#include <ctime>
static long long ps[2005][2005]; // 1-based 前缀和，多开一圈做 0 边界

int main() {
    // clock_t start = clock();
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return 0;

    // 构建二维前缀和
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            long long v;
            scanf("%lld", &v);
            // 计算前缀和
            ps[i][j] = v + ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
        }
    }

    int q; 
    scanf("%d", &q);
    // 处理每个查询
    while (q--) {
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        int r = x + a - 1;
        int c = y + b - 1;
        // 利用前缀和计算子矩阵和
        long long ans = ps[r][c] - ps[x - 1][c] - ps[r][y - 1] + ps[x - 1][y - 1];
        printf("%lld\n", ans);
    }
    // clock_t end = clock();
    // double time_taken = double(end - start) / CLOCKS_PER_SEC;
    // printf("solution_3 time: %f seconds\n", time_taken);
    return 0;
}
