

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

static inline void iswap(int &a, int &b) { int t = a; a = b; b = t; }

int n, m, K, q;

// 堆节点
int *hL, *hR, *hDist;
int *hKey; // 点权（0..1e9）

// 左式堆合并：返回新根
static int heapMerge(int x, int y) {
    if (x == 0) return y;
    if (y == 0) return x;
    if (hKey[x] > hKey[y]) iswap(x, y); // 小根堆：根更小
    hR[x] = heapMerge(hR[x], y);
    if (hDist[hL[x]] < hDist[hR[x]]) iswap(hL[x], hR[x]);
    hDist[x] = hDist[hR[x]] + 1;
    return x;
}

// 弹出堆顶
static inline int heapPop(int x) {
    return heapMerge(hL[x], hR[x]);
}

int *fa;
int *compSz;     // 连通块真实点数
int *heapRoot;   // 该块的堆根
int *heapSz;     // 堆中节点数

static inline int findSet(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

// 合并两个点所在连通块
static inline void unite(int u, int v) {
    int ru = findSet(u);
    int rv = findSet(v);
    if (ru == rv) return;

    // 按真实块大小合并
    if (compSz[ru] < compSz[rv]) iswap(ru, rv);

    // rv 挂到 ru
    fa[rv] = ru;
    compSz[ru] += compSz[rv];

    // 合并 top-k 堆
    heapRoot[ru] = heapMerge(heapRoot[ru], heapRoot[rv]);
    heapSz[ru] += heapSz[rv];

    // 保持堆大小不超过 K
    while (heapSz[ru] > K) {
        heapRoot[ru] = heapPop(heapRoot[ru]);
        heapSz[ru]--;
    }
}

static const int OUT_BUF_SIZE = 1 << 22; 
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

int main() {
    n = readInt();
    m = readInt();
    K = readInt();
    q = readInt();

    fa = (int*)std::malloc(sizeof(int) * (n + 1));
    compSz = (int*)std::malloc(sizeof(int) * (n + 1));
    heapRoot = (int*)std::malloc(sizeof(int) * (n + 1));
    heapSz = (int*)std::malloc(sizeof(int) * (n + 1));

    hL = (int*)std::malloc(sizeof(int) * (n + 1));
    hR = (int*)std::malloc(sizeof(int) * (n + 1));
    hDist = (int*)std::malloc(sizeof(int) * (n + 1));
    hKey = (int*)std::malloc(sizeof(int) * (n + 1));

    OUT_BUF = (char*)std::malloc(OUT_BUF_SIZE);

    if (!fa || !compSz || !heapRoot || !heapSz || !hL || !hR || !hDist || !hKey || !OUT_BUF) {

        return 0;
    }

    // 初始化空节点
    hL[0] = hR[0] = 0;
    hDist[0] = 0;
    hKey[0] = 0;

    // 读点权 & 初始化每个点为一个堆
    for (int i = 1; i <= n; i++) {
        int w = readInt();
        hKey[i] = w;
        hL[i] = hR[i] = 0;
        hDist[i] = 1;

        fa[i] = i;
        compSz[i] = 1;
        heapRoot[i] = i;
        heapSz[i] = 1;
    }

    // 初始边并入
    for (int i = 0; i < m; i++) {
        int u = readInt();
        int v = readInt();
        unite(u, v);
    }

    long long queryCnt = 0, addCnt = 0;

    // 操作
    for (int i = 0; i < q; i++) {
        int op = readInt();
        if (op == 1) {
            int u = readInt();
            int v = readInt();
            unite(u, v);
            addCnt++;
        } else {
            int u = readInt();
            int r = findSet(u);
            queryCnt++;
            if (compSz[r] < K) {
                outInt(-1);
            } else {
                int root = heapRoot[r];
                outInt(hKey[root]);
            }
        }
    }

    // flush 输出
    if (OUT_POS) std::fwrite(OUT_BUF, 1, OUT_POS, stdout);

    DBG("[DEBUG] n=%d m=%d K=%d q=%d, add=%lld, query=%lld\n",
        n, m, K, q, addCnt, queryCnt);

    std::free(fa);
    std::free(compSz);
    std::free(heapRoot);
    std::free(heapSz);
    std::free(hL);
    std::free(hR);
    std::free(hDist);
    std::free(hKey);
    std::free(OUT_BUF);

    return 0;
}
