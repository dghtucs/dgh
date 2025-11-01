#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int imax(int a, int b) { return a > b ? a : b; }
static inline int imin(int a, int b) { return a < b ? a : b; }
static inline int iabs(int x) { return x < 0 ? -x : x; }

int main()
{
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    int N, M, K;
    if (scanf("%d %d %d", &N, &M, &K) != 3)
        return 0;

    // 动态分配内存用于存储两个字符串
    char *A = (char *)malloc((N + 1) * sizeof(char));
    char *B = (char *)malloc((M + 1) * sizeof(char));
    if (!A || !B)
        return 0;

    scanf("%s", A);
    scanf("%s", B);

    if (iabs(N - M) > K)
    {
        printf("-1\n");
        free(A);
        free(B);
        return 0;
    }
    if (K == 0)
    {
        printf("%d\n", strcmp(A, B) == 0 ? 0 : -1);
        free(A);
        free(B);
        return 0;
    }

    // 确保 N <= M：把短串放前面，便于带状
    if (N > M)
    {
        int tN = N;
        N = M;
        M = tN;
        char *tS = A;
        A = B;
        B = tS;
    }

    const int INF = K + 1;

    // i=0 的基线：dp[0][j] = j（仅插入）
    int pL = 0, pR = imin(M, K);
    int pLen = pR - pL + 1;
    int *prev = (int *)malloc(pLen * sizeof(int));
    if (!prev)
        return 0;
    for (int j = pL; j <= pR; ++j)
        prev[j - pL] = j;

    int *cur = NULL;
    int jL, jR, len;

    for (int i = 1; i <= N; ++i)
    {
        jL = imax(0, i - K);
        jR = imin(M, i + K);
        len = jR - jL + 1;
        cur = (int *)malloc(len * sizeof(int));
        if (!cur)
            return 0;
        for (int t = 0; t < len; ++t)
            cur[t] = INF;

// 取上一行 dp[i-1][j]
#define GET_PREV(jidx) (((jidx) < pL || (jidx) > pR) ? INF : prev[(jidx) - pL])

        for (int j = jL; j <= jR; ++j)
        {
            int best = INF;

            // 删除 A[i-1]
            int up = GET_PREV(j);
            if (up + 1 < best)
                best = up + 1;

            // 插入 B[j-1]
            if (j > jL)
            {
                int left = cur[(j - 1) - jL] + 1;
                if (left < best)
                    best = left;
            }
            else if (j == 0)
            {
                // dp[i][0] = i（只能删）
                if (i < best)
                    best = i;
            }

            // 斜对角：匹配或“删+插”(成本2)
            if (j > 0)
            {
                int diag = GET_PREV(j - 1);
                if (diag < INF)
                {
                    int cost = (A[i - 1] == B[j - 1]) ? 0 : 2;
                    if (diag + cost < best)
                        best = diag + cost;
                }
            }

            if (best > K + 1)
                best = K + 1; // 截断
            cur[j - jL] = best;
        }

        free(prev);
        prev = cur;
        pL = jL;
        pR = jR;
        pLen = len;
    }

    int final_jL = imax(0, N - K);
    int ans = prev[M - final_jL];
    printf("%d\n", (ans <= K ? ans : -1));

    free(prev);
    free(A);
    free(B);
    return 0;
}
