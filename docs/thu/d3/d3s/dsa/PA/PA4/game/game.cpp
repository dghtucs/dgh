
#include <cstdio>
#include <cstring>

static const int MAXN = 100000 + 5;
static const int MAXM = 100000 + 5;
static const int MAXE = 2 * MAXM + 5;
static const int MAXHEAP = 400000 + 5; 
static const int MOD = 1000000007;
static const long long INF = (1LL << 62);


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


int head[MAXN];
int to[MAXE];
int nxt[MAXE];
int ecnt = 0;

static inline void addEdge(int u, int v) {
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
    ecnt++;
}


long long heapD[MAXHEAP];
int heapV[MAXHEAP];
int hsz = 0;

static inline void heapSwap(int i, int j) {
    long long td = heapD[i]; heapD[i] = heapD[j]; heapD[j] = td;
    int tv = heapV[i]; heapV[i] = heapV[j]; heapV[j] = tv;
}

static inline void heapPush(int v, long long d) {
    ++hsz;
    heapV[hsz] = v;
    heapD[hsz] = d;
    int i = hsz;
    while (i > 1) {
        int p = i >> 1;
        if (heapD[p] <= heapD[i]) break;
        heapSwap(p, i);
        i = p;
    }
}

static inline int heapPop(int &v, long long &d) {
    if (hsz == 0) return 0;
    v = heapV[1];
    d = heapD[1];
    heapV[1] = heapV[hsz];
    heapD[1] = heapD[hsz];
    --hsz;

    int i = 1;
    while (1) {
        int l = i << 1;
        int r = l + 1;
        int s = i;
        if (l <= hsz && heapD[l] < heapD[s]) s = l;
        if (r <= hsz && heapD[r] < heapD[s]) s = r;
        if (s == i) break;
        heapSwap(i, s);
        i = s;
    }
    return 1;
}


int N, M;
int t[MAXN];
long long dista[MAXN];
int ways[MAXN];
char vis[MAXN];

int main() {
    N = readInt();
    M = readInt();

    for (int i = 1; i <= N; i++) t[i] = readInt();

    // 初始化邻接表
    for (int i = 1; i <= N; i++) head[i] = -1;

    for (int i = 0; i < M; i++) {
        int u = readInt();
        int v = readInt();
        addEdge(u, v);
        addEdge(v, u);
    }

    // 初始化最短路
    for (int i = 1; i <= N; i++) {
        dista[i] = INF;
        ways[i] = 0;
        vis[i] = 0;
    }

    dista[1] = (long long)t[1];
    ways[1] = 1;
    heapPush(1, dista[1]);


#ifdef DEBUG
    fprintf(stderr, "[DEBUG] start dijkstra, dist[1]=%lld\n", dista[1]);
#endif

    while (hsz > 0) {
        int u;
        long long d;
        heapPop(u, d);

        // 重复入堆的旧状态直接跳过
        if (d != dista[u]) continue;
        if (vis[u]) continue;
        vis[u] = 1;

#ifdef DEBUG
        fprintf(stderr, "[DEBUG] pop u=%d, dist=%lld, ways=%d\n", u, dista[u], ways[u]);
#endif

        if (u == N) break; // Dijkstra：到N已是最短

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (vis[v]) {
                continue;
            }
            long long nd = dista[u] + (long long)t[v];

            if (nd < dista[v]) {
                dista[v] = nd;
                ways[v] = ways[u];
                heapPush(v, nd);

#ifdef DEBUG
                fprintf(stderr, "  [DEBUG] relax v=%d newdist=%lld ways=%d\n", v, nd, ways[v]);
#endif

            } else if (nd == dista[v]) {
                int nv = ways[v] + ways[u];
                if (nv >= MOD) nv -= MOD;
                ways[v] = nv;

#ifdef DEBUG
                fprintf(stderr, "  [DEBUG] tie v=%d dist=%lld addways -> %d\n", v, nd, ways[v]);
#endif
            }
        }
    }


    printf("%lld\n", dista[N]);
    printf("%d\n", ways[N] % MOD);

#ifdef DEBUG
    fprintf(stderr, "[DEBUG] done. dist[N]=%lld ways[N]=%d\n", dista[N], ways[N]);
#endif

    return 0;
}

