

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef DEBUG
#define DBG(...) std::fprintf(stderr, __VA_ARGS__)
#else
#define DBG(...) ((void)0)
#endif

static const int IN_BUF_SIZE = 1 << 20;
static unsigned char IN_BUF[IN_BUF_SIZE];
static int IN_LEN = 0, IN_POS = 0;

static inline int nextChar() {
    if (IN_POS >= IN_LEN) {
        IN_LEN = (int)std::fread(IN_BUF, 1, IN_BUF_SIZE, stdin);
        IN_POS = 0;
        if (IN_LEN <= 0) return -1;
    }
    return IN_BUF[IN_POS++];
}

static inline int readInt() {
    int c = nextChar();
    while (c <= ' ' && c != -1) c = nextChar();
    int x = 0;
    while (c > ' ') {
        x = x * 10 + (c - '0');
        c = nextChar();
    }
    return x;
}

static const int OUT_BUF_SIZE = 1 << 22; // 4MB
static char *OUT_BUF;
static int OUT_POS = 0;

static inline void outInt(int x) {
    if (OUT_POS > OUT_BUF_SIZE - 32) {
        std::fwrite(OUT_BUF, 1, OUT_POS, stdout);
        OUT_POS = 0;
    }
    if (x == 0) {
        OUT_BUF[OUT_POS++] = '0';
        OUT_BUF[OUT_POS++] = '\n';
        return;
    }
    if (x < 0) {
        OUT_BUF[OUT_POS++] = '-';
        x = -x;
    }
    char s[16];
    int p = 0;
    while (x > 0) {
        s[p++] = (char)('0' + (x % 10));
        x /= 10;
    }
    while (p--) OUT_BUF[OUT_POS++] = s[p];
    OUT_BUF[OUT_POS++] = '\n';
}

static const int MAX_ADD = 1000000;          
static const int MAXLOG = 22;                 

int *val;     // 音符值
int *pi;      // KMP 前缀函数
int *dep;     // 失配树深度
int *up[MAXLOG]; 

static inline int iMin(int a, int b) { return a < b ? a : b; }


static inline void extend_one(int pos) {
    if (pos == 1) {
        pi[1] = 0;
    } else {
        int j = pi[pos - 1];
        while (j > 0 && val[j + 1] != val[pos]) j = pi[j];
        if (val[j + 1] == val[pos]) ++j;
        pi[pos] = j;
    }

    dep[pos] = dep[pi[pos]] + 1;
    up[0][pos] = pi[pos];
    for (int k = 1; k < MAXLOG; ++k) {
        int mid = up[k - 1][pos];
        up[k][pos] = (mid ? up[k - 1][mid] : 0);
    }
}

// 二者 LCA
static inline int lca2(int a, int b) {
    if (a == b) return a;
    if (dep[a] < dep[b]) { int t = a; a = b; b = t; }

    int diff = dep[a] - dep[b];
    for (int k = 0; k < MAXLOG; ++k) {
        if (diff & (1 << k)) a = up[k][a];
    }
    if (a == b) return a;

    for (int k = MAXLOG - 1; k >= 0; --k) {
        if (up[k][a] != up[k][b]) {
            a = up[k][a];
            b = up[k][b];
        }
    }
    return up[0][a];
}

static inline int clamp_to_limit(int u, int limit) {
    if (u <= limit) return u;
    for (int k = MAXLOG - 1; k >= 0; --k) {
        int p = up[k][u];
        if (p > limit) u = p;
    }
    return up[0][u];
}

int main() {
    int n = readInt();
    int m = readInt();

    int maxLen = n + MAX_ADD + 5; // 总长度上界

    // 分配数组
    val = (int*)std::malloc(sizeof(int) * (maxLen));
    pi  = (int*)std::malloc(sizeof(int) * (maxLen));
    dep = (int*)std::malloc(sizeof(int) * (maxLen));
    OUT_BUF = (char*)std::malloc(OUT_BUF_SIZE);

    if (!val || !pi || !dep || !OUT_BUF) return 0;
    for (int k = 0; k < MAXLOG; ++k) {
        up[k] = (int*)std::malloc(sizeof(int) * (maxLen));
        if (!up[k]) return 0;
    }

    // 初始化 0 号节点
    val[0] = 0;
    pi[0] = 0;
    dep[0] = 0;
    for (int k = 0; k < MAXLOG; ++k) up[k][0] = 0;

    // 读初始序列并建 pi
    int len = n;
    for (int i = 1; i <= n; ++i) {
        val[i] = readInt();
    }
    for (int i = 1; i <= n; ++i) {
        extend_one(i);
    }

    DBG("[DEBUG] init done, len=%d\n", len);

    // 处理操作
    for (int opi = 0; opi < m; ++opi) {
        int op = readInt();
        if (op == 1) {
            int q = readInt();
            for (int i = 0; i < q; ++i) {
                ++len;
                val[len] = readInt();
                extend_one(len);
            }
#ifdef DEBUG
            DBG("[DEBUG] append q=%d, new len=%d\n", q, len);
#endif
        } else {
            int q = readInt();
            int curLCA = 0;
            int minD = 1 << 30;

            // 读第一个
            if (q > 0) {
                int d = readInt();
                curLCA = d;
                minD = d;
                // 其余
                for (int i = 1; i < q; ++i) {
                    d = readInt();
                    if (d < minD) minD = d;
                    curLCA = lca2(curLCA, d);
                }
            }

            int limit = minD / 2;        
            int ans = clamp_to_limit(curLCA, limit);
            outInt(ans);

#ifdef DEBUG
            DBG("[DEBUG] query q=%d, minD=%d, rawLCA=%d, limit=%d, ans=%d\n",
                q, minD, curLCA, limit, ans);
#endif
        }
    }

    if (OUT_POS) std::fwrite(OUT_BUF, 1, OUT_POS, stdout);

    for (int k = 0; k < MAXLOG; ++k) std::free(up[k]);
    std::free(val);
    std::free(pi);
    std::free(dep);
    std::free(OUT_BUF);

    return 0;
}
