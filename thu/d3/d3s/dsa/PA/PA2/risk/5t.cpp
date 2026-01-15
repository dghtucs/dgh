#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *x = (int*)malloc((n + 1) * sizeof(int));
    unsigned int *m = (unsigned int*)malloc((n + 1) * sizeof(unsigned int));
    if (!x || !m) return 0;

    int maxX = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x[i]);
        if (x[i] > maxX) maxX = x[i];
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%u", &m[i]);
    }

    // 单调队列（存下标和对应值），实现最大值队列
    int *dq_idx = (int*)malloc((n + 1) * sizeof(int));
    int *dq_val = (int*)malloc((n + 1) * sizeof(int));
    if (!dq_idx || !dq_val) return 0;
    int head = 0, tail = 0; // [head, tail)

    // 频次数组与前缀数组（直接在 freq 上做前缀和）
    int freqSize = maxX + 1; // K 只会落在 [0..maxX]
    int *freq = (int*)calloc(freqSize, sizeof(int));
    if (!freq) return 0;

    // 逐日计算 K_i，并计数
    for (int i = 1; i <= n; ++i) {
        long long L = (long long)i - (long long)m[i]; // 窗口为 [L, i-1]
        // 移除窗口左侧之外的元素
        while (head < tail && (long long)dq_idx[head] < L) head++;

        int k = (head < tail) ? dq_val[head] : 0; // 队列空则最大值为 0
        // 记录 K_i 的出现次数
        freq[k]++;

        // 将当天 x[i] 入队（供后续天使用，窗口是“前 m_i 天”，不含当天）
        while (head < tail && dq_val[tail - 1] <= x[i]) tail--;
        dq_idx[tail] = i;
        dq_val[tail] = x[i];
        tail++;
    }

    // 前缀和：freq[v] 变为 <= v 的天数
    for (int v = 1; v <= maxX; ++v) freq[v] += freq[v - 1];

    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; ++t) {
        unsigned int p, q;
        scanf("%u %u", &p, &q);

        // 计算 < threshold 的数量
        int less_p, less_q;
        if (p == 0) less_p = 0;
        else if (p - 1 >= (unsigned int)maxX) less_p = freq[maxX];
        else less_p = freq[p - 1];

        if (q == 0) less_q = 0; // 题目保证 p < q
        else if (q - 1 >= (unsigned int)maxX) less_q = freq[maxX];
        else less_q = freq[q - 1];

        int low = less_p;
        int mid = less_q - less_p;
        printf("%d %d\n", low, mid);
    }

    free(x);
    free(m);
    free(dq_idx);
    free(dq_val);
    free(freq);
    return 0;
}
