

#include <cstdio>
#include <cstdlib>
#include <cstdint>

static const int MAXD = 5;
static const int MAXN = 100000;
static const int BUCKET = 16;
static const long long INF64 = (1LL<<62);

struct FastIO {
    static inline int gc() {
#if defined(_WIN32) || defined(_WIN64)
        return getchar();
#else
        return getchar_unlocked();
#endif
    }
    static inline bool readInt(int &out) {
        int c = gc();
        while (c != EOF && c <= ' ') c = gc();
        if (c == EOF) return false;
        int sgn = 1;
        if (c == '-') { sgn = -1; c = gc(); }
        int x = 0;
        while (c > ' ') {
            x = x * 10 + (c - '0');
            c = gc();
        }
        out = x * sgn;
        return true;
    }

    static inline void writeLL(long long x) {
        static char buf[32];
        int n = 0;
        if (x == 0) {
#if defined(_WIN32) || defined(_WIN64)
            putchar('0'); putchar('\n');
#else
            putchar_unlocked('0'); putchar_unlocked('\n');
#endif
            return;
        }
        if (x < 0) {
#if defined(_WIN32) || defined(_WIN64)
            putchar('-');
#else
            putchar_unlocked('-');
#endif
            x = -x;
        }
        while (x) {
            buf[n++] = char('0' + (x % 10));
            x /= 10;
        }
        for (int i = n - 1; i >= 0; --i) {
#if defined(_WIN32) || defined(_WIN64)
            putchar(buf[i]);
#else
            putchar_unlocked(buf[i]);
#endif
        }
#if defined(_WIN32) || defined(_WIN64)
        putchar('\n');
#else
        putchar_unlocked('\n');
#endif
    }
};

int D, N;

struct Point {
    int c[MAXD];
};

static Point pts[MAXN];

static inline void swapPoint(Point &a, Point &b) {
    Point t = a;
    a = b;
    b = t;
}

static void quickSelect(int l, int r, int k, int dim) {
    while (r - l > 1) {
        int pivot = pts[(l + r) >> 1].c[dim];
        int i = l, j = r - 1;
        while (i <= j) {
            while (pts[i].c[dim] < pivot) ++i;
            while (pts[j].c[dim] > pivot) --j;
            if (i <= j) {
                swapPoint(pts[i], pts[j]);
                ++i; --j;
            }
        }
        if (k <= j) r = j + 1;
        else if (k >= i) l = i;
        else return;
    }
}

struct Node {
    // bbox
    int mn[MAXD], mx[MAXD];

    // children
    int lc, rc;

    // split
    int axis;
    int isLeaf;

    // leaf range [L, R)
    int L, R;

    // internal point
    Point p;
};

static Node nodes[MAXN + 5];
static int nodeCnt = 0;

static inline void initBBoxFromPoint(Node &nd, const Point &p) {
    for (int i = 0; i < D; ++i) nd.mn[i] = nd.mx[i] = p.c[i];
}

static inline void expandBBoxWithPoint(Node &nd, const Point &p) {
    for (int i = 0; i < D; ++i) {
        if (p.c[i] < nd.mn[i]) nd.mn[i] = p.c[i];
        if (p.c[i] > nd.mx[i]) nd.mx[i] = p.c[i];
    }
}

static inline void expandBBoxWithChild(Node &nd, int childId) {
    const Node &ch = nodes[childId];
    for (int i = 0; i < D; ++i) {
        if (ch.mn[i] < nd.mn[i]) nd.mn[i] = ch.mn[i];
        if (ch.mx[i] > nd.mx[i]) nd.mx[i] = ch.mx[i];
    }
}

static int build(int l, int r, int depth) {
    int id = ++nodeCnt;
    Node &nd = nodes[id];
    nd.lc = nd.rc = 0;

    if (r - l <= BUCKET) {
        nd.isLeaf = 1;
        nd.L = l; nd.R = r;
        initBBoxFromPoint(nd, pts[l]);
        for (int i = l + 1; i < r; ++i) expandBBoxWithPoint(nd, pts[i]);
        return id;
    }

    nd.isLeaf = 0;
    nd.axis = depth % D;
    int mid = (l + r) >> 1;
    quickSelect(l, r, mid, nd.axis);

    nd.p = pts[mid];
    initBBoxFromPoint(nd, nd.p);

    if (l < mid) {
        nd.lc = build(l, mid, depth + 1);
        expandBBoxWithChild(nd, nd.lc);
    }
    if (mid + 1 < r) {
        nd.rc = build(mid + 1, r, depth + 1);
        expandBBoxWithChild(nd, nd.rc);
    }
    return id;
}

static inline long long dist2Point(const Point &a, const int q[]) {
    long long s = 0;
    for (int i = 0; i < D; ++i) {
        long long d = (long long)a.c[i] - (long long)q[i];
        s += d * d;
    }
    return s;
}

static inline long long dist2BBox(const Node &nd, const int q[]) {
    long long s = 0;
    for (int i = 0; i < D; ++i) {
        long long v = q[i];
        if (v < nd.mn[i]) {
            long long d = (long long)nd.mn[i] - v;
            s += d * d;
        } else if (v > nd.mx[i]) {
            long long d = v - (long long)nd.mx[i];
            s += d * d;
        }
    }
    return s;
}

static long long bestAns;
static int queryPt[MAXD];

static void query(int id) {
    if (!id) return;
    const Node &nd = nodes[id];

    if (dist2BBox(nd, queryPt) > bestAns) return;

    if (nd.isLeaf) {
        for (int i = nd.L; i < nd.R; ++i) {
            long long d2 = dist2Point(pts[i], queryPt);
            if (d2 < bestAns) bestAns = d2;
        }
        return;
    }

    long long d2p = dist2Point(nd.p, queryPt);
    if (d2p < bestAns) bestAns = d2p;

    int ax = nd.axis;
    int goLeftFirst = (queryPt[ax] <= nd.p.c[ax]);

    int first = goLeftFirst ? nd.lc : nd.rc;
    int second = goLeftFirst ? nd.rc : nd.lc;

    if (first) query(first);
    if (second) query(second);
}

int main() {
    if (!FastIO::readInt(D)) return 0;
    FastIO::readInt(N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < D; ++j) FastIO::readInt(pts[i].c[j]);
    }

    int root = build(0, N, 0);

    int Q;
    FastIO::readInt(Q);
    for (int qi = 0; qi < Q; ++qi) {
        for (int j = 0; j < D; ++j) FastIO::readInt(queryPt[j]);
        bestAns = INF64;
        query(root);
        FastIO::writeLL(bestAns);
    }
    return 0;
}
