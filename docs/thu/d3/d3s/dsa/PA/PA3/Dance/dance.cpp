#include <cstdio>

class FastIO {
public:
    static inline int gc() {
#ifdef _WIN32
        return getchar();
#else
        return getchar_unlocked();
#endif
    }
    static inline void pc(char c) {
#ifdef _WIN32
        putchar(c);
#else
        putchar_unlocked(c);
#endif
    }
    static inline void readChar(char &c) {
        int x;
        do { x = gc(); } while (x <= ' ' && x != EOF);
        c = (char)x;
    }
    static inline void readInt(int &x) {
        int c = gc();
        while (c <= ' ' && c != EOF) c = gc();
        int sgn = 1;
        if (c == '-') { sgn = -1; c = gc(); }
        long long v = 0;
        while (c >= '0' && c <= '9') {
            v = v * 10 + (c - '0');
            c = gc();
        }
        x = (int)(v * sgn);
    }
    static inline void writeInt(int x) {
        if (x == 0) { pc('0'); return; }
        if (x < 0) { pc('-'); x = -x; }
        char s[16];
        int n = 0;
        while (x) { s[n++] = (char)('0' + (x % 10)); x /= 10; }
        while (n--) pc(s[n]);
    }
};

static const int MAXM = 500000;
static const int MAXN = MAXM + 5;

struct Node {
    int l, r;
    int sz;
    unsigned pri;
    unsigned char rev;
    int val;
};

static Node tr[MAXN];
static int tot = 0;
static int root = 0;

static unsigned rng_state = 2463534242u;
static inline unsigned rng() {
    unsigned x = rng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng_state = x;
    return x;
}

static inline int sz(int x) { return x ? tr[x].sz : 0; }

static inline void pushUp(int x) {
    tr[x].sz = sz(tr[x].l) + sz(tr[x].r) + 1;
}

static inline void applyRev(int x) {
    if (!x) return;
    tr[x].rev ^= 1;
    int t = tr[x].l; tr[x].l = tr[x].r; tr[x].r = t;
}

static inline void pushDown(int x) {
    if (!x || !tr[x].rev) return;
    applyRev(tr[x].l);
    applyRev(tr[x].r);
    tr[x].rev = 0;
}

static inline int newNode(int v) {
    ++tot;
    tr[tot].l = tr[tot].r = 0;
    tr[tot].sz = 1;
    tr[tot].pri = rng();
    tr[tot].rev = 0;
    tr[tot].val = v;
    return tot;
}

static void split(int cur, int k, int &a, int &b) {
    if (!cur) { a = b = 0; return; }
    pushDown(cur);
    if (sz(tr[cur].l) >= k) {
        b = cur;
        split(tr[cur].l, k, a, tr[b].l);
        pushUp(b);
    } else {
        a = cur;
        split(tr[cur].r, k - sz(tr[cur].l) - 1, tr[a].r, b);
        pushUp(a);
    }
}

static int merge(int a, int b) {
    if (!a || !b) return a ? a : b;
    if (tr[a].pri < tr[b].pri) {
        pushDown(a);
        tr[a].r = merge(tr[a].r, b);
        pushUp(a);
        return a;
    } else {
        pushDown(b);
        tr[b].l = merge(a, tr[b].l);
        pushUp(b);
        return b;
    }
}

static int kth(int cur, int k) { // 1..sz
    while (cur) {
        pushDown(cur);
        int ls = sz(tr[cur].l);
        if (k <= ls) cur = tr[cur].l;
        else if (k == ls + 1) return cur;
        else { k -= ls + 1; cur = tr[cur].r; }
    }
    return 0;
}

static inline int modPos(long long x, int n) {
    long long r = x % n;
    if (r < 0) r += n;
    return (int)r;
}

static void insertAt(int pos, int v) {
    int a, b;
    split(root, pos, a, b);
    int nd = newNode(v);
    root = merge(merge(a, nd), b);
}

static void reverseRange(int l, int r) {
    if (l >= r) return;
    int a, b, c;
    split(root, l, a, b);
    split(b, r - l + 1, b, c);
    applyRev(b);
    root = merge(merge(a, b), c);
}

static void rotateLeftPhysical(int k, int &head, int n) {
    if (n == 0) return;
    k %= n;
    if (k < 0) k += n;
    if (k == 0) return;
    int a, b;
    split(root, k, a, b);
    root = merge(b, a);
    head -= k;
    if (head < 0) head += n;
}

static void swapPos(int p, int q) {
    if (p == q) return;
    int x = kth(root, p + 1);
    int y = kth(root, q + 1);
    int t = tr[x].val;
    tr[x].val = tr[y].val;
    tr[y].val = t;
}

static int arr[MAXN];
static int stk[MAXN];

static int dumpInorder(int rt) {
    int top = 0, idx = 0;
    int cur = rt;
    while (cur || top) {
        while (cur) {
            pushDown(cur);
            stk[top++] = cur;
            cur = tr[cur].l;
        }
        cur = stk[--top];
        arr[idx++] = tr[cur].val;
        cur = tr[cur].r;
    }
    return idx;
}

int main() {
    int N, M;
    FastIO::readInt(N);
    FastIO::readInt(M);

    int n = 0;
    int head = 0; 

    for (int t = 0; t < M; ++t) {
        char op;
        FastIO::readChar(op);

        if (op == 'I') {
            int x, p;
            FastIO::readInt(x);
            FastIO::readInt(p);

            if (n == 0) {
                insertAt(0, x);
                n = 1;
                head = 0;
            } else {
                int pos;
                if (p == n) pos = head;           
                else pos = (head + p) % n;        
                insertAt(pos, x);

                if (p != 0) {
                    if (pos <= head) head++;
                    if (head >= n + 1) head -= (n + 1);
                }
                n++;
            }
        } else if (op == 'S') {
            int i, j;
            FastIO::readInt(i);
            FastIO::readInt(j);
            int pi = (head + i) % n;
            int pj = (head + j) % n;
            swapPos(pi, pj);
        } else if (op == 'R') {
            int r;
            FastIO::readInt(r);
            head = modPos((long long)head - (long long)r, n); // O(1)
        } else if (op == 'F') {
            int i, j;
            FastIO::readInt(i);
            FastIO::readInt(j);
            int len = (j - i + n) % n + 1;
            if (len <= 1) continue;

            int st = (head + i) % n; // physical start

            if (st + len <= n) {
                reverseRange(st, st + len - 1);
            } else {
                // rotate so st -> 0, reverse prefix len, rotate back
                rotateLeftPhysical(st, head, n);
                reverseRange(0, len - 1);
                rotateLeftPhysical(n - st, head, n);
            }
        }
    }

    int cnt = dumpInorder(root); // cnt == n
    for (int i = 0; i < cnt; ++i) {
        if (i) FastIO::pc(' ');
        int p = head + i;
        if (p >= cnt) p -= cnt;
        FastIO::writeInt(arr[p]);
    }
    FastIO::pc('\n');
    return 0;
}
