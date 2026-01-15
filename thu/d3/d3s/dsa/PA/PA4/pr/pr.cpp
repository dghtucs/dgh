

#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef unsigned long long ULL;

static const int MAXM = 2000 + 5;
static const int MAXN = 1000 + 5;


static const ULL BASE_X1 = 911382323ULL;
static const ULL BASE_X2 = 972663749ULL;
static const ULL BASE_Y1 = 97266353ULL;
static const ULL BASE_Y2 = 1000003ULL;

static const int HT_POW = 22;
static const int HT_CAP = (1 << HT_POW);
static const int HT_MASK = HT_CAP - 1;

static inline int readInt() {
    int c = getchar_unlocked();
    while (c <= ' ' && c != EOF) c = getchar_unlocked();
    int x = 0;
    while (c > ' ') {
        x = x * 10 + (c - '0');
        c = getchar_unlocked();
    }
    return x;
}

static inline void readWord(char *s) {
    int c = getchar_unlocked();
    while (c <= ' ' && c != EOF) c = getchar_unlocked();
    int i = 0;
    while (c > ' ') {
        s[i++] = (char)c;
        c = getchar_unlocked();
    }
    s[i] = '\0';
}


static inline ULL mix64(ULL x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}


static ULL *ht_k1 = NULL;
static ULL *ht_k2 = NULL;
static int *ht_val = NULL;
static unsigned char *ht_used = NULL;

static inline void ht_init() {
    ht_k1 = (ULL*)malloc(sizeof(ULL) * HT_CAP);
    ht_k2 = (ULL*)malloc(sizeof(ULL) * HT_CAP);
    ht_val = (int*)malloc(sizeof(int) * HT_CAP);
    ht_used = (unsigned char*)malloc(sizeof(unsigned char) * HT_CAP);

    if (!ht_k1 || !ht_k2 || !ht_val || !ht_used) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(0);
    }
    memset(ht_used, 0, sizeof(unsigned char) * HT_CAP);
}

static inline void ht_add(ULL a, ULL b) {
    ULL h = mix64(a ^ (b * 1315423911ULL));
    int idx = (int)(h & HT_MASK);

    while (ht_used[idx]) {
        if (ht_k1[idx] == a && ht_k2[idx] == b) {
            ht_val[idx] += 1;
            return;
        }
        idx = (idx + 1) & HT_MASK;
    }
    ht_used[idx] = 1;
    ht_k1[idx] = a;
    ht_k2[idx] = b;
    ht_val[idx] = 1;
}

static inline int ht_get(ULL a, ULL b) {
    ULL h = mix64(a ^ (b * 1315423911ULL));
    int idx = (int)(h & HT_MASK);

    while (ht_used[idx]) {
        if (ht_k1[idx] == a && ht_k2[idx] == b) return ht_val[idx];
        idx = (idx + 1) & HT_MASK;
    }
    return 0;
}


static ULL powX1[MAXN], powX2[MAXN];
static ULL powY1[MAXM], powY2[MAXM];

// 行前缀
static ULL pref1[MAXN], pref2[MAXN];

// 竖向前缀
static ULL vpref1[MAXM], vpref2[MAXM];

int main() {
    int M = readInt();
    int N = readInt();
    int m = readInt();
    int n = readInt();
    int k = readInt();

#ifdef DEBUG
    fprintf(stderr, "[DEBUG] M=%d N=%d m=%d n=%d k=%d\n", M, N, m, n, k);
#endif

    // 预计算幂
    powX1[0] = 1; powX2[0] = 1;
    for (int i = 1; i <= N; i++) {
        powX1[i] = powX1[i - 1] * BASE_X1;
        powX2[i] = powX2[i - 1] * BASE_X2;
    }
    powY1[0] = 1; powY2[0] = 1;
    for (int i = 1; i <= M; i++) {
        powY1[i] = powY1[i - 1] * BASE_Y1;
        powY2[i] = powY2[i - 1] * BASE_Y2;
    }

    // 读入T
    char *line = (char*)malloc((N + 5) * sizeof(char));
    if (!line) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 0;
    }

    int W = N - n + 1;       // 每行可取的起点个数
    int H = M - m + 1;       // 可取的顶部起点个数

#ifdef DEBUG
    fprintf(stderr, "[DEBUG] W=%d H=%d\n", W, H);
#endif


    int possible = (W > 0 && H > 0);


    ULL *row1 = NULL;
    ULL *row2 = NULL;
    long long rowSize = 0;

    if (possible) {
        rowSize = 1LL * M * W;
        row1 = (ULL*)malloc(sizeof(ULL) * rowSize);
        row2 = (ULL*)malloc(sizeof(ULL) * rowSize);
        if (!row1 || !row2) {
            fprintf(stderr, "Memory allocation failed for row hashes!\n");
            return 0;
        }
    }

    // 逐行读取T，并计算该行所有长度n子串哈希
    for (int i = 0; i < M; i++) {
        readWord(line); // 长度N

        if (!possible) continue;

        // 计算前缀哈希
        pref1[0] = 0; pref2[0] = 0;
        for (int j = 0; j < N; j++) {
            ULL v = (ULL)(unsigned char)line[j];
            pref1[j + 1] = pref1[j] * BASE_X1 + v;
            pref2[j + 1] = pref2[j] * BASE_X2 + v;
        }

        // 计算长度n子串哈希
        long long base = 1LL * i * W;
        for (int j = 0; j < W; j++) {
            int l = j;
            int r = j + n;
            ULL h1 = pref1[r] - pref1[l] * powX1[n];
            ULL h2 = pref2[r] - pref2[l] * powX2[n];
            row1[base + j] = h1;
            row2[base + j] = h2;
        }

#ifdef DEBUG
        if (i == 0 && W > 0) {
            fprintf(stderr, "[DEBUG] sample rowHash(0,0): h1=%llu h2=%llu\n",
                    (unsigned long long)row1[0], (unsigned long long)row2[0]);
        }
#endif
    }


    if (possible) {
        ht_init();

        // 对每个列起点j，做竖向前缀，再取长度m区间
        for (int j = 0; j < W; j++) {
            vpref1[0] = 0;
            vpref2[0] = 0;

            // 构建竖向前缀：vpref[i+1] = vpref[i]*BASE_Y + rowHash[i][j]
            for (int i = 0; i < M; i++) {
                long long idx = 1LL * i * W + j;
                vpref1[i + 1] = vpref1[i] * BASE_Y1 + row1[idx];
                vpref2[i + 1] = vpref2[i] * BASE_Y2 + row2[idx];
            }

            // 枚举顶部起点i，取长度m
            for (int i = 0; i < H; i++) {
                ULL h1 = vpref1[i + m] - vpref1[i] * powY1[m];
                ULL h2 = vpref2[i + m] - vpref2[i] * powY2[m];
                ht_add(h1, h2);
            }
        }

#ifdef DEBUG
        fprintf(stderr, "[DEBUG] hash table built.\n");
#endif
    }

    // 逐个模式读入、计算二维哈希、查询并输出
    char *pline = (char*)malloc((n + 5) * sizeof(char));
    if (!pline) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 0;
    }

    for (int pi = 0; pi < k; pi++) {
        ULL ph1 = 0, ph2 = 0;

        for (int r = 0; r < m; r++) {
            readWord(pline); 

            // 计算该行整行哈希
            ULL rh1 = 0, rh2 = 0;
            for (int c = 0; c < n; c++) {
                ULL v = (ULL)(unsigned char)pline[c];
                rh1 = rh1 * BASE_X1 + v;
                rh2 = rh2 * BASE_X2 + v;
            }

            // 竖向合并：patternHash = patternHash*BASE_Y + rowHash
            ph1 = ph1 * BASE_Y1 + rh1;
            ph2 = ph2 * BASE_Y2 + rh2;
        }

        int ans = 0;
        if (possible) ans = ht_get(ph1, ph2);

#ifdef DEBUG
        if (pi < 3) {
            fprintf(stderr, "[DEBUG] pattern %d hash: h1=%llu h2=%llu ans=%d\n",
                    pi + 1, (unsigned long long)ph1, (unsigned long long)ph2, ans);
        }
#endif

        printf("%d\n", ans);
    }

    // 释放内存
    free(line);
    free(pline);
    if (row1) free(row1);
    if (row2) free(row2);
    if (ht_k1) free(ht_k1);
    if (ht_k2) free(ht_k2);
    if (ht_val) free(ht_val);
    if (ht_used) free(ht_used);

    return 0;
}


