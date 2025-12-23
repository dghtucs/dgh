#include <cstdio>
#include <cstdlib>
#include <cstring>

/*
  CST 2-3-3 Build(hard)
  只用 scanf/printf；无 STL/algorithm。

  思路要点：
  - 孩子用双向兄弟链（head/tail/next/prev/deg）。
  - 路径按“最长合法前缀”定位；kth_child 按 rank 沿链走（成本计入题目所说总成本）。
  - 规模 sz[]：切/接子树时，必须向根一路加/减（不可早停）。
  - 高度 h[]：每个结点维护“孩子高度最大堆”（Skew Heap，懒删除 + 版本号）。
    pull_height() 里读取堆顶，若高度不变即可在向上传播时早停。
*/

static const int MAXCOST = 1000000;  // 题面保证所有操作成本和 ≤ 1e6

/* ---------- 读整数 ---------- */
static inline int read_int() { int x; scanf("%d", &x); return x; }

/* ---------- 全局数据 ---------- */
int N, M;

/* 树结构（动态变化） */
int *parent_;      // parent_[u]
int *head, *tail;  // u 的第一个/最后一个孩子
int *next_, *prev_; // 兄弟链指针
int *deg;          // 孩子数量
int *sz;           // 子树规模
int *h;            // 子树高度（边数）

/* ---------- 每个结点的“孩子高度最大堆”（Skew Heap） ---------- */
int *heapRoot; // 每个结点的堆根
int *ver;      // 每个结点的“版本号”（父子变化/高度变化时递增）

struct HN {
    int key;   // child's height
    int ch;    // child id
    int ver;   // snapshot version when pushed
    int l, r;  // skew-heap children
};
HN *H = NULL;
int Hcap = 0, Htot = 0;

static inline void heap_reserve(int need) {
    if (need <= Hcap) return;
    int ncap = (Hcap ? Hcap : 4);
    while (ncap < need) ncap <<= 1;
    H = (HN*)realloc(H, ncap * sizeof(HN));
    Hcap = ncap;
}
static inline int newHN(int key, int ch, int vv) {
    if (Htot + 1 >= Hcap) heap_reserve(Htot + 1);
    ++Htot;
    H[Htot].key = key; H[Htot].ch = ch; H[Htot].ver = vv; H[Htot].l = 0; H[Htot].r = 0;
    return Htot;
}
static int heap_merge(int x, int y) { // max-heap
    if (!x) return y;
    if (!y) return x;
    if (H[x].key < H[y].key) { int t = x; x = y; y = t; }
    int nx = H[x].l;
    H[x].l = H[x].r;
    H[x].r = heap_merge(nx, y);
    return x;
}
static inline void heap_push(int u, int key, int ch, int vv) {
    int nd = newHN(key, ch, vv);
    heapRoot[u] = heap_merge(heapRoot[u], nd);
}
static inline void heap_pop(int &root) {
    root = heap_merge(H[root].l, H[root].r);
}
static inline int heap_top_valid_key(int u) {
    int r = heapRoot[u];
    while (r) {
        int v = H[r].ch;
        if (parent_[v] != u || H[r].ver != ver[v]) { heap_pop(r); heapRoot[u] = r; continue; }
        return H[r].key;
    }
    return -1; // 无孩子
}

/* ---------- 工具：取第 rank 个孩子（0-based；若不存在返回 0） ---------- */
static inline int kth_child(int u, int rank) {
    int v = head[u];
    while (rank-- > 0 && v) v = next_[v];
    return v ? v : 0;
}

/* ---------- 路径读取与定位（最长合法前缀） ---------- */
int *pathBuf;
static inline int read_path_into_buf() {
    int m = read_int();
    for (int i = 0; i < m; ++i) pathBuf[i] = read_int();
    return m;
}
static inline int locate_by_path(int m) {
    int u = 1;
    for (int i = 0; i < m; ++i) {
        int rk = pathBuf[i];
        if (rk < 0 || rk >= deg[u]) break;
        int v = kth_child(u, rk);
        if (!v) break;
        u = v;
    }
    return u;
}

/* ---------- 更新结点 u 的高度；若变化则把新高度压入父的堆 ---------- */
static inline int pull_height(int u) {
    int oldh = h[u];
    int maxc = (deg[u] == 0) ? -1 : heap_top_valid_key(u);
    int newh = (maxc < 0 ? 0 : (1 + maxc));
    if (newh == oldh) return 0;
    h[u] = newh;
    int p = parent_[u];
    if (p) { ++ver[u]; heap_push(p, h[u], u, ver[u]); }
    return 1;
}

/* ---------- 从当前父亲处切下子树 s ---------- */
static inline void detach(int s) {
    int p = parent_[s];
    if (!p) return; // 根节点不会被切（题面：真子树）；防御
    // 从兄弟链摘除
    int L = prev_[s], R = next_[s];
    if (L) next_[L] = R; else head[p] = R;
    if (R) prev_[R] = L; else tail[p] = L;
    prev_[s] = next_[s] = 0;
    parent_[s] = 0;
    --deg[p];
    ++ver[s];  // 让 p 的堆里关于 s 的旧条目失效

    // —— 规模必须一路更新到根 —— //
    int delta = sz[s];
    for (int u = p; u; u = parent_[u]) sz[u] -= delta;

    // —— 高度向上传播，遇到不变即可早停 —— //
    for (int u = p; u; u = parent_[u]) {
        if (!pull_height(u)) break;
    }
}

/* ---------- 把子树 s 接到 d 的第 k 个孩子位置（k 可越界到尾部） ---------- */
static inline void attach(int s, int d, int k) {
    if (k < 0) k = 0;
    if (k > deg[d]) k = deg[d];

    if (k == 0) {
        int old = head[d];
        prev_[s] = 0; next_[s] = old;
        if (old) prev_[old] = s; else tail[d] = s;
        head[d] = s;
    } else if (k == deg[d]) {
        int old = tail[d];
        next_[s] = 0; prev_[s] = old;
        if (old) next_[old] = s; else head[d] = s;
        tail[d] = s;
    } else {
        int t = kth_child(d, k);
        int L = prev_[t];
        next_[s] = t; prev_[s] = L;
        prev_[t] = s;
        if (L) next_[L] = s; else head[d] = s;
    }
    parent_[s] = d;
    ++deg[d];

    // 把 s 的高度插进 d 的堆（懒删除：需要刷新版本）
    ++ver[s];
    heap_push(d, h[s], s, ver[s]);

    // —— 规模必须一路更新到根 —— //
    int delta = sz[s];
    for (int u = d; u; u = parent_[u]) sz[u] += delta;

    // —— 高度向上传播 —— //
    for (int u = d; u; u = parent_[u]) {
        if (!pull_height(u)) break;
    }
}

int main() {
    N = read_int(); M = read_int();

    parent_ = (int*)calloc(N + 1, sizeof(int));
    head    = (int*)calloc(N + 1, sizeof(int));
    tail    = (int*)calloc(N + 1, sizeof(int));
    next_   = (int*)calloc(N + 1, sizeof(int));
    prev_   = (int*)calloc(N + 1, sizeof(int));
    deg     = (int*)calloc(N + 1, sizeof(int));
    sz      = (int*)calloc(N + 1, sizeof(int));
    h       = (int*)calloc(N + 1, sizeof(int));
    heapRoot= (int*)calloc(N + 1, sizeof(int));
    ver     = (int*)calloc(N + 1, sizeof(int));
    pathBuf = (int*)malloc((MAXCOST + 5) * sizeof(int));
    if (!parent_ || !head || !tail || !next_ || !prev_ || !deg || !sz || !h || !heapRoot || !ver || !pathBuf) return 0;

    /* ---- 读孩子节点表示法，搭建兄弟链 ---- */
    for (int u = 1; u <= N; ++u) {
        int d = read_int();
        deg[u] = d;
        int last = 0;
        for (int j = 0; j < d; ++j) {
            int v = read_int();
            parent_[v] = u;
            if (last == 0) head[u] = v;
            else next_[last] = v;
            prev_[v] = last;
            last = v;
        }
        tail[u] = last;
    }

    /* ---- 非递归后序：计算初始 sz/h ----
       为避免找第 i 个孩子的 O(i) 累加，这里每个结点维护一个“当前孩子游标”。 */
    int *cur = (int*)calloc(N + 1, sizeof(int));
    int *stk = (int*)malloc((N + 5) * sizeof(int));
    int top = 0;
    stk[top++] = 1;

    while (top) {
        int u = stk[top - 1];
        if (cur[u] == 0) cur[u] = head[u]; // 初始化游标
        if (cur[u]) {
            int v = cur[u];
            cur[u] = next_[v];
            stk[top++] = v;
        } else {
            // 处理 u
            int sizeu = 1;
            int maxh = -1;
            int v = head[u];
            while (v) {
                sizeu += sz[v];
                if (h[v] > maxh) maxh = h[v];
                v = next_[v];
            }
            sz[u] = sizeu;
            h[u]  = (maxh < 0 ? 0 : 1 + maxh);
            --top;
        }
    }
    free(cur);
    free(stk);

    /* ---- 建堆（每条父->子关系压一次） ---- */
    Hcap = 0; Htot = 0; H = NULL;
    heap_reserve((N > 1 ? N - 1 : 1) + 2 * (MAXCOST + 100));
    for (int u = 1; u <= N; ++u) heapRoot[u] = 0;
    for (int u = 1; u <= N; ++u) {
        int v = head[u];
        while (v) {
            heap_push(u, h[v], v, ver[v]); // ver[v] 初始为 0
            v = next_[v];
        }
    }

    /* ---- 处理操作 ---- */
    for (int opi = 0; opi < M; ++opi) {
        int type = read_int();
        if (type == 0) {
            // 移动：读 s、切下；读 d；读 k；接入
            int ms = read_path_into_buf();
            int s = locate_by_path(ms);
            detach(s);

            int md = read_path_into_buf();
            int d = locate_by_path(md);

            int k = read_int();
            if (s != 1) attach(s, d, k); // 题面“真子树”；防御
        } else if (type == 1) {
            // 高度查询
            int mq = read_path_into_buf();
            int u = locate_by_path(mq);
            printf("%d\n", h[u]);
        } else { // type == 2
            // 规模查询
            int mq = read_path_into_buf();
            int u = locate_by_path(mq);
            printf("%d\n", sz[u]);
        }
    }

    /* ---- 释放（OJ 可省略） ---- */
    free(parent_); free(head); free(tail); free(next_); free(prev_);
    free(deg); free(sz); free(h); free(heapRoot); free(ver);
    free(H); free(pathBuf);
    return 0;
}
