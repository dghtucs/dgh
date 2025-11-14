#include <cstdio>
#include <cstdlib>
#include <cstring>



int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    // 邻接（孩子表）
    int *cnt = (int*)malloc((N + 1) * sizeof(int));          // 每节点孩子数
    int *pos = (int*)malloc((N + 1) * sizeof(int));          // 在 child[] 中起始位置
    int *parent = (int*)calloc(N + 1, sizeof(int));          // 父亲（root 的父为 0）
    int *child = (int*)malloc(((N > 1 ? N - 1 : 1)) * sizeof(int)); // 存所有孩子编号
    if (!cnt || !pos || !parent || !child) return 0;

    int ptr = 0;
    for (int u = 1; u <= N; ++u) {
        int d; if (scanf("%d", &d) != 1) d = 0;
        cnt[u] = d;
        pos[u] = ptr;
        for (int j = 0; j < d; ++j) {
            int v; scanf("%d", &v);
            child[ptr++] = v;
            parent[v] = u;
        }
    }

    // 内力值（互不相同）
    int *a = (int*)malloc((N + 1) * sizeof(int));
    for (int i = 1; i <= N; ++i) scanf("%d", &a[i]);

    // ---------- 真·非递归后序，计算子树和 ----------
    int *stk_u = (int*)malloc((N + 5) * sizeof(int));
    int *stk_i = (int*)malloc((N + 5) * sizeof(int)); // 指向下一个要处理的孩子偏移 [0..cnt[u])
    unsigned long long *subsum = (unsigned long long*)malloc((N + 1) * sizeof(unsigned long long));
    if (!stk_u || !stk_i || !subsum) return 0;

    int top = 0;
    stk_u[top] = 1; stk_i[top] = 0; ++top;

    // 初始化
    for (int i = 1; i <= N; ++i) subsum[i] = 0ULL;

    while (top) {
        int u = stk_u[top - 1];
        int idx = stk_i[top - 1];
        if (idx < cnt[u]) {
            int v = child[pos[u] + idx];
            stk_i[top - 1] = idx + 1;
            stk_u[top] = v; stk_i[top] = 0; ++top;
        } else {
            unsigned long long s = (unsigned long long)a[u];
            int p0 = pos[u], c0 = cnt[u];
            for (int t = 0; t < c0; ++t) s += subsum[ child[p0 + t] ];
            subsum[u] = s;
            --top;
        }
    }

    // ---------- 选“正统弟子” ----------
    int *heir = (int*)calloc(N + 1, sizeof(int));
    if (!heir) return 0;
    for (int u = 1; u <= N; ++u) {
        if (cnt[u] == 0) continue;
        unsigned long long best = 0ULL;
        int bestId = 0;
        int p0 = pos[u];
        for (int t = 0; t < cnt[u]; ++t) {
            int v = child[p0 + t];
            unsigned long long sv = subsum[v];
            if (sv > best || (sv == best && v < bestId)) {
                best = sv; bestId = v;
            }
        }
        heir[u] = bestId; // 若只有一个孩子也会被记录为它
    }

    // ---------- 构造“传承边”形成的链：up[v]（若允许向上）与 down[u] ----------
    int *up = (int*)calloc(N + 1, sizeof(int));
    int *down = (int*)calloc(N + 1, sizeof(int));
    if (!up || !down) return 0;

    for (int v = 2; v <= N; ++v) {
        int p = parent[v];
        if (cnt[p] == 1 || heir[p] == v) { // 两种情况允许向上
            up[v] = p;
            down[p] = v; // 每个父最多一条传承边，安全
        }
    }

    // ---------- 在每条链上做单调栈，找“左侧最近更大” ----------
    int *ans = (int*)malloc((N + 1) * sizeof(int));
    for (int i = 1; i <= N; ++i) ans[i] = -1;

    int *mstack = (int*)malloc((N + 5) * sizeof(int)); // 存节点编号，维护 a[] 严格递减
    int mt = 0;

    for (int head = 1; head <= N; ++head) {
        if (up[head] != 0) continue; // 只从链头出发
        mt = 0;
        int u = head;
        while (1) {
            while (mt > 0 && a[mstack[mt - 1]] <= a[u]) --mt; // 保持栈中 a[] 递减
            ans[u] = (mt > 0 ? mstack[mt - 1] : -1);
            mstack[mt++] = u;
            if (down[u] == 0) break;
            u = down[u];
        }
    }

    // ---------- 输出 ----------
    for (int i = 1; i <= N; ++i) {
        printf("%d\n", ans[i]);
    }

    // ---------- 释放 ----------
    free(cnt); free(pos); free(parent); free(child);
    free(a); free(stk_u); free(stk_i); free(subsum); free(heir);
    free(up); free(down); free(ans); free(mstack);
    return 0;
}
