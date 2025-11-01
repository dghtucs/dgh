// #include <cstdio>

// int matrix[2000][2000];

// int main() {
//     int n, m, q;
//     scanf("%d%d", &n, &m);
//     for (int i = 1; i <= n; ++i) {
//         for (int j = 1; j <= m; ++j) {
//             scanf("%d", &matrix[i][j]);
//         }
//     }
//     scanf("%d", &q);
//     int sum = 0;
//     for (int i = 1; i <= q; ++i) {
//         int x, y, a, b;
//         scanf("%d %d %d %d", &x, &y, &a, &b);
//         for (int j = 0; j < a; ++j) {
//             for (int k = 0; k < b; ++k) {
//                 sum += matrix[x + j][y + k];
//             }
//         }
//         printf("%d\n", sum);
//     }
//     return 0;
// }


// solution_1.cpp —— 朴素做法：O(a*b) 每次查询
#include <cstdio>
#include <ctime>

static int matrix[2005][2005];  // 1-based，多开一圈避免越界

int main() {
    clock_t start = clock();
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return 0;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &matrix[i][j]);

    int q; 
    scanf("%d", &q);
    while (q--) {
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        long long sum = 0;  // 每次询问重新累计
        for (int i = 0; i < a; ++i)
            for (int j = 0; j < b; ++j)
                sum += matrix[x + i][y + j];
        printf("%lld\n", sum);
    }
    clock_t end = clock();
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    printf("solution_1 time: %f seconds\n", time_taken);
    return 0;
}
