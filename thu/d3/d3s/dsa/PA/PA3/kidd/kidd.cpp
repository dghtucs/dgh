#include <cstdio>
#include <cstdlib>

class FastIO {
public:
    static inline int gc() {
#ifdef _WIN32
        return getchar();
#else
        return getchar_unlocked();
#endif
    }
    static inline void readChar(char &c) {
        int x;
        do { x = gc(); } while (x <= ' ' && x != EOF);
        c = (char)x;
    }
    static inline void readLL(long long &x) {
        int c = gc();
        while (c <= ' ' && c != EOF) c = gc();
        int sgn = 1;
        if (c == '-') { sgn = -1; c = gc(); }
        unsigned long long v = 0;
        while (c >= '0' && c <= '9') {
            v = v * 10 + (unsigned)(c - '0');
            c = gc();
        }
        x = (long long)(v * (unsigned long long)sgn);
    }
    static inline void writeLL(long long x) {
#ifdef _WIN32
        if (x == 0) { putchar('0'); putchar('\n'); return; }
        if (x < 0) { putchar('-'); x = -x; }
        char s[32]; int n = 0;
        while (x) { s[n++] = char('0' + (x % 10)); x /= 10; }
        while (n--) putchar(s[n]);
        putchar('\n');
#else
        if (x == 0) { putchar_unlocked('0'); putchar_unlocked('\n'); return; }
        if (x < 0) { putchar_unlocked('-'); x = -x; }
        char s[32]; int n = 0;
        while (x) { s[n++] = char('0' + (x % 10)); x /= 10; }
        while (n--) putchar_unlocked(s[n]);
        putchar_unlocked('\n');
#endif
    }
};

static const int MAXNODE = 6500000;

static int lc[MAXNODE + 5], rc[MAXNODE + 5];
static int lazyTag[MAXNODE + 5];
static long long segSum[MAXNODE + 5];
static int tot = 0;

static inline int newNode() {
    ++tot;
    if (tot > MAXNODE) std::exit(0);
    lc[tot] = rc[tot] = 0;
    lazyTag[tot] = 0;
    segSum[tot] = 0;
    return tot;
}

static inline long long overlapLen(long long L, long long R, long long ql, long long qr) {
    long long a = (L > ql ? L : ql);
    long long b = (R < qr ? R : qr);
    if (a > b) return 0;
    return b - a + 1;
}

static void update(int p, long long L, long long R, long long ql, long long qr) {
    if (ql <= L && R <= qr) {
        lazyTag[p] += 1;
        segSum[p] += (R - L + 1);
        return;
    }
    long long mid = (L + R) >> 1;
    if (ql <= mid) {
        if (!lc[p]) lc[p] = newNode();
        update(lc[p], L, mid, ql, qr);
    }
    if (qr > mid) {
        if (!rc[p]) rc[p] = newNode();
        update(rc[p], mid + 1, R, ql, qr);
    }
    long long len = (R - L + 1);
    long long leftSum = lc[p] ? segSum[lc[p]] : 0LL;
    long long rightSum = rc[p] ? segSum[rc[p]] : 0LL;
    segSum[p] = leftSum + rightSum + (long long)lazyTag[p] * len;
}

static long long query(int p, long long L, long long R, long long ql, long long qr) {
    if (!p) return 0LL;
    if (ql <= L && R <= qr) return segSum[p];
    long long ans = (long long)lazyTag[p] * overlapLen(L, R, ql, qr);
    long long mid = (L + R) >> 1;
    if (ql <= mid) ans += query(lc[p], L, mid, ql, qr);
    if (qr > mid) ans += query(rc[p], mid + 1, R, ql, qr);
    return ans;
}

int main() {
    long long n, m;
    FastIO::readLL(n);
    FastIO::readLL(m);

    tot = 0;
    int root = newNode();

    for (long long i = 0; i < m; ++i) {
        char op;
        long long s, t;
        FastIO::readChar(op);
        FastIO::readLL(s);
        FastIO::readLL(t);
        if (op == 'H') update(root, 1LL, n, s, t);
        else FastIO::writeLL(query(root, 1LL, n, s, t));
    }
    return 0;
}
