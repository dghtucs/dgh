// #include <cstdio>

// int matrix[2000][2000];
// int rowsum[2000][2000];

// int main() {
//     int n, m, q;
//     scanf("%d%d", &n, &m);
//     for (int i = 1; i <= n; ++i) {
//         for (int j = 1; j <= m; ++j) {
//             scanf("%d", &matrix[i][j]);
//         }
//     }
//     for (int i = 1; i <= n; ++i) {
//         rowsum[i][0] = 0;
//         for (int j = 1; j <= m; ++j) {
//             rowsum[i][j] = rowsum[i][j - 1] + matrix[i][j];
//         }
//     }
//     scanf("%d", &q);
//     int sum = 0;
//     for (int i = 1; i <= q; ++i) {
//         int x, y, a, b;
//         scanf("%d %d %d %d", &x, &y, &a, &b);
//         for (int j = 0; j < a; ++j) {
//             sum += rowsum[x + j][y + b] - rowsum[x + j][y];
//         }
//         printf("%d\n", sum);
//     }
//     return 0;
// }


// solution_2.cpp —— 行前缀和：每次查询 O(a)
#include <cstdio>

static int matrix[2005][2005];
static long long rowsum[2005][2005];  // rowsum[i][j] = 第 i 行前 j 个元素之和

int main() {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return 0;

    for (int i = 1; i <= n; ++i) {
        rowsum[i][0] = 0;  // 便于处理 y-1 = 0 的边界
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &matrix[i][j]);
            rowsum[i][j] = rowsum[i][j - 1] + matrix[i][j];
        }
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        long long sum = 0;  // 每次询问重新累计
        for (int i = 0; i < a; ++i) {
            int r = x + i;
            // 区间 [y, y+b-1] 的行和：rowsum[r][y+b-1] - rowsum[r][y-1]
            sum += rowsum[r][y + b - 1] - rowsum[r][y - 1];
        }
        printf("%lld\n", sum);
    }
    return 0;
}
