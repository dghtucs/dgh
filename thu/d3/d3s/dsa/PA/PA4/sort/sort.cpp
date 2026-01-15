

#include "sort.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

static long long g_cmp_cnt = 0; 

#ifdef DEBUG
#define DBG(...) std::fprintf(stderr, __VA_ARGS__)
#else
#define DBG(...) ((void)0)
#endif


static inline void CMP(int a, int b, int c, int *mx, int *mn) {
    ++g_cmp_cnt;
    compare(a, b, c, mx, mn);
}

// 三个互不相同编号的中位数
static inline int MED3(int x, int y, int z, int mn, int mx) {
    return x ^ y ^ z ^ mn ^ mx;
}


static inline void sort3(int *arr, int p) {
    int x = arr[p], y = arr[p + 1], z = arr[p + 2];
    int mx, mn;
    CMP(x, y, z, &mx, &mn);
    int md = MED3(x, y, z, mn, mx);
    arr[p] = mn;
    arr[p + 1] = md;
    arr[p + 2] = mx;
}


static inline void insert_small(int *buf, int len, int x) {
    int mn0 = buf[0];
    int mx0 = buf[len - 1];

    int tmx, tmn;
    CMP(x, mn0, mx0, &tmx, &tmn);

    if (tmn == x) {
        for (int i = len; i >= 1; --i) buf[i] = buf[i - 1];
        buf[0] = x;
        return;
    }
    if (tmx == x) {
        buf[len] = x;
        return;
    }

    // 此时 x 在 (mn0, mx0)，mn0 一定是更小 guard
    int pos = len;
    for (int i = 1; i < len; ++i) {
        int cmx, cmn;
        CMP(x, buf[i], mn0, &cmx, &cmn);
        if (cmx == buf[i]) { pos = i; break; }
    }
    for (int i = len; i > pos; --i) buf[i] = buf[i - 1];
    buf[pos] = x;
}

// 排序 4 个
static inline void sort4(int *arr, int p) {
    int tmp[5];
    tmp[0] = arr[p];
    tmp[1] = arr[p + 1];
    tmp[2] = arr[p + 2];
    tmp[3] = arr[p + 3];

    // 先排前3个
    int mx, mn;
    CMP(tmp[0], tmp[1], tmp[2], &mx, &mn);
    int md = MED3(tmp[0], tmp[1], tmp[2], mn, mx);

    int buf[5];
    buf[0] = mn; buf[1] = md; buf[2] = mx;

    // 插入第4个
    insert_small(buf, 3, tmp[3]);

    arr[p] = buf[0];
    arr[p + 1] = buf[1];
    arr[p + 2] = buf[2];
    arr[p + 3] = buf[3];
}

// 排序 5 个
static inline void sort5(int *arr, int p) {
    int tmp[5];
    for (int i = 0; i < 5; ++i) tmp[i] = arr[p + i];

    // 先排前3个
    int mx, mn;
    CMP(tmp[0], tmp[1], tmp[2], &mx, &mn);
    int md = MED3(tmp[0], tmp[1], tmp[2], mn, mx);

    int buf[6];
    buf[0] = mn; buf[1] = md; buf[2] = mx;

    // 插入第4、第5
    insert_small(buf, 3, tmp[3]);
    insert_small(buf, 4, tmp[4]);

    for (int i = 0; i < 5; ++i) arr[p + i] = buf[i];
}

static void merge_adaptive(const int *src, int *dst, int L, int M, int R) {
    int i = L, j = M, k = L;
    int mode = 0;      
    int streak = 0;    

    while (i < M && j < R) {
        if (i == M - 1 && j == R - 1) {
            if (k == L) {
                if (i + 1 < M) {
                    int mx, mn;
                    CMP(src[i], src[i + 1], src[j], &mx, &mn);
                    if (mn == src[j]) { dst[k++] = src[j]; ++j; }
                    else if (mx == src[j]) { dst[k++] = src[i]; dst[k++] = src[i + 1]; i += 2; }
                    else { dst[k++] = src[i]; dst[k++] = src[j]; ++i; ++j; }
                    continue;
                }
            }
            int guard = dst[k - 1];
            int mx, mn;
            CMP(src[i], src[j], guard, &mx, &mn);
            if (mx == src[i]) { dst[k++] = src[j]; dst[k++] = src[i]; }
            else { dst[k++] = src[i]; dst[k++] = src[j]; }
            ++i; ++j;
            break;
        }

        if (mode == 0) {
            // 需要左边至少2个，否则切换
            if (i + 1 >= M) { mode = 1; streak = 0; continue; }

            int a0 = src[i], a1 = src[i + 1], b0 = src[j];
            int mx, mn;
            CMP(a0, a1, b0, &mx, &mn);

            if (mn == b0) {
                // b0 最小：只输出 b0
                dst[k++] = b0;
                ++j;
                ++streak;
                // 连续两次右头最小 -> 切换到 mode=1
                if (streak >= 2 && j + 1 < R) { mode = 1; streak = 0; }
            } else if (mx == b0) {
                // b0 最大：输出 a0,a1
                dst[k++] = a0;
                dst[k++] = a1;
                i += 2;
                streak = 0;
            } else {
                // b0 中间：输出 a0,b0
                dst[k++] = a0;
                dst[k++] = b0;
                ++i; ++j;
                streak = 0;
            }
        } else {
            // mode==1：需要右边至少2个，否则切换
            if (j + 1 >= R) { mode = 0; streak = 0; continue; }

            int b0 = src[j], b1 = src[j + 1], a0 = src[i];
            int mx, mn;
            CMP(b0, b1, a0, &mx, &mn);

            if (mn == a0) {
                // a0 最小：只输出 a0
                dst[k++] = a0;
                ++i;
                ++streak;
                // 连续两次左头最小 -> 切换到 mode=0（前提左边还能取2个）
                if (streak >= 2 && i + 1 < M) { mode = 0; streak = 0; }
            } else if (mx == a0) {
                // a0 最大：输出 b0,b1
                dst[k++] = b0;
                dst[k++] = b1;
                j += 2;
                streak = 0;
            } else {
                // a0 中间：输出 b0,a0
                dst[k++] = b0;
                dst[k++] = a0;
                ++j; ++i;
                streak = 0;
            }
        }
    }

    while (i < M) dst[k++] = src[i++];
    while (j < R) dst[k++] = src[j++];
}

void sort(int n, int limit, int *a) {
    (void)limit; 
    g_cmp_cnt = 0;

    if (n <= 1) return;

    // 辅助数组
    int *buf = (int*)std::malloc(sizeof(int) * (size_t)n);
    if (!buf) return;

    // run 长度数组
    int maxRuns = n / 3 + 5;
    int *run1 = (int*)std::malloc(sizeof(int) * (size_t)maxRuns);
    int *run2 = (int*)std::malloc(sizeof(int) * (size_t)maxRuns);
    if (!run1 || !run2) {
        if (run1) std::free(run1);
        if (run2) std::free(run2);
        std::free(buf);
        return;
    }

    int runCnt = 0;
    int full3 = n / 3;
    int r = n % 3;

    for (int i = 0; i < full3; ++i) run1[runCnt++] = 3;

    if (r == 1) {
        // 借一个 3 变 4
        if (runCnt >= 1) run1[runCnt - 1] = 4;
        else { run1[runCnt++] = 4; }
    } else if (r == 2) {
        // 借一个 3 变 5
        if (runCnt >= 1) run1[runCnt - 1] = 5;
        else { run1[runCnt++] = 5; }
    }

    if (n < 9) {
        runCnt = 1;
        run1[0] = n;
    }

    // 先把每个 run 原地排序
    int pos = 0;
    for (int i = 0; i < runCnt; ++i) {
        int len = run1[i];
        if (len == 3) sort3(a, pos);
        else if (len == 4) sort4(a, pos);
        else if (len == 5) sort5(a, pos);
        else {
            // len<=8：先排前三，再逐个插入
            sort3(a, pos);
            int tmp[10];
            tmp[0] = a[pos];
            tmp[1] = a[pos + 1];
            tmp[2] = a[pos + 2];
            int curLen = 3;
            for (int t = 3; t < len; ++t) {
                int x = a[pos + t];
                insert_small(tmp, curLen, x);
                ++curLen;
            }
            for (int t = 0; t < len; ++t) a[pos + t] = tmp[t];
        }
        pos += len;
    }

    DBG("[DEBUG] initial runs=%d, cmp_cnt=%lld\n", runCnt, g_cmp_cnt);

    // 迭代归并 runs
    int *src = a;
    int *dst = buf;
    int *curRuns = run1;
    int *nxtRuns = run2;

    while (runCnt > 1) {
        int outCnt = 0;
        int offset = 0;

        for (int i = 0; i < runCnt; i += 2) {
            int len1 = curRuns[i];
            if (i + 1 < runCnt) {
                int len2 = curRuns[i + 1];
                merge_adaptive(src, dst, offset, offset + len1, offset + len1 + len2);
                nxtRuns[outCnt++] = len1 + len2;
                offset += (len1 + len2);
            } else {
                // 奇数个 run：最后一个直接拷贝
                for (int p = 0; p < len1; ++p) dst[offset + p] = src[offset + p];
                nxtRuns[outCnt++] = len1;
                offset += len1;
            }
        }

        // swap
        int *tmpA = src; src = dst; dst = tmpA;
        int *tmpR = curRuns; curRuns = nxtRuns; nxtRuns = tmpR;
        runCnt = outCnt;

        DBG("[DEBUG] merge round done, runs=%d, cmp_cnt=%lld\n", runCnt, g_cmp_cnt);
    }

    if (src != a) {
        for (int i = 0; i < n; ++i) a[i] = src[i];
    }

    std::free(buf);
    std::free(run1);
    std::free(run2);

    DBG("[DEBUG] sort done, total cmp_cnt=%lld\n", g_cmp_cnt);
}
