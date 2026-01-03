#include <cstdio>
int main() {
    freopen("03.in", "w", stdout);
    const int n = 500000;      // 初始长度
    const int m = 500000;      // 操作次数
    // 初始串：AB 交替，不含三连
    for (int i = 0; i < n; ++i) putchar((i & 1) ? 'B' : 'A');
    putchar('\n');
    // m 行操作
    printf("%d\n", m);
    // 每次都头插，颜色在 C / D 交替，保证不形成三连
    for (int i = 0; i < m; ++i) {
        printf("0 %c\n", (i & 1) ? 'D' : 'C');
    }
    return 0;
}