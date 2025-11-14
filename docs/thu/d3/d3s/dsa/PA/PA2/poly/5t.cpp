#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>

static const unsigned long long MOD = 1000000007ULL;
static const int MAXD = 64; 


static inline unsigned long long addmod(unsigned long long a, unsigned long long b){
    unsigned long long s = a + b;
    if (s >= MOD) s -= MOD;
    return s;
}
static inline unsigned long long submod(unsigned long long a, unsigned long long b){
    return (a >= b) ? (a - b) : (a + MOD - b);
}
static inline unsigned long long mulmod(unsigned long long a, unsigned long long b){
    __int128 z = (__int128)a * (__int128)b;
    unsigned long long r = (unsigned long long)(z % MOD);
    return r;
}
static inline unsigned long long powmod(unsigned long long a, unsigned int e){
    unsigned long long r = 1ULL;
    while (e){
        if (e & 1U) r = mulmod(r, a);
        a = mulmod(a, a);
        e >>= 1U;
    }
    return r;
}

// --------- 多项式表示 ----------
struct Poly {
    // type: 0 常数；1 单项式；2 一般式（arr 指向长度 MAXD+1 的数组）
    int type;
    int deg;                    // 单项式/一般式的次数；常数置 0
    unsigned long long c;       // 常数值 或 单项式系数
    unsigned long long *arr;    // 一般式系数指针，arr[i] 是 x^i 的系数
};

static inline void poly_set_const(Poly &p, unsigned long long c){
    p.type = 0; p.deg = 0; p.c = c % MOD; p.arr = NULL;
}
static inline void poly_set_x(Poly &p){
    p.type = 1; p.deg = 1; p.c = 1ULL; p.arr = NULL;
}
static inline void poly_release(Poly &p){
    if (p.type == 2 && p.arr){ free(p.arr); }
    p.type = 0; p.deg = 0; p.c = 0; p.arr = NULL;
}
static inline Poly poly_clone(const Poly &p){
    Poly r; r.type = p.type; r.deg = p.deg; r.c = p.c; r.arr = NULL;
    if (p.type == 2){
        r.arr = (unsigned long long*)malloc((MAXD+1) * sizeof(unsigned long long));
        for (int i = 0; i <= MAXD; ++i) r.arr[i] = p.arr[i];
    }
    return r;
}
static inline void poly_from_full(Poly &p, unsigned long long *buf){ // 接管 buf
    p.type = 2; p.arr = buf;
    int d = MAXD;
    while (d > 0 && p.arr[d] == 0ULL) --d;
    if (d == 0 && p.arr[0] == 0ULL){
        // 变成 0 常数
        free(p.arr); p.arr = NULL;
        poly_set_const(p, 0ULL);
    }else if (d == 0){
        unsigned long long c0 = p.arr[0];
        free(p.arr); p.arr = NULL;
        poly_set_const(p, c0);
    }else{
        p.deg = d;
    }
}
static inline Poly poly_from_monomial(unsigned long long coef, int deg){
    Poly r;
    coef %= MOD;
    if (coef == 0ULL){
        poly_set_const(r, 0ULL);
    }else if (deg == 0){
        poly_set_const(r, coef);
    }else{
        r.type = 1; r.deg = deg; r.c = coef; r.arr = NULL;
    }
    return r;
}

// --------- 多项式运算 ----------
static inline Poly poly_add(const Poly &A, const Poly &B){
    // 常数
    if (A.type == 0 && B.type == 0){
        Poly r; poly_set_const(r, addmod(A.c, B.c)); return r;
    }
    // 单项式 + 单项式
    if (A.type == 1 && B.type == 1){
        if (A.deg == B.deg){
            unsigned long long c = addmod(A.c, B.c);
            return poly_from_monomial(c, A.deg);
        }else{
            unsigned long long *buf = (unsigned long long*)calloc(MAXD+1, sizeof(unsigned long long));
            buf[A.deg] = addmod(buf[A.deg], A.c);
            buf[B.deg] = addmod(buf[B.deg], B.c);
            Poly r; poly_from_full(r, buf); return r;
        }
    }
    // 常数 + 单项式
    if (A.type == 0 && B.type == 1){
        unsigned long long *buf = (unsigned long long*)calloc(MAXD+1, sizeof(unsigned long long));
        buf[0] = addmod(buf[0], A.c);
        buf[B.deg] = addmod(buf[B.deg], B.c);
        Poly r; poly_from_full(r, buf); return r;
    }
    if (A.type == 1 && B.type == 0){
        unsigned long long *buf = (unsigned long long*)calloc(MAXD+1, sizeof(unsigned long long));
        buf[0] = addmod(buf[0], B.c);
        buf[A.deg] = addmod(buf[A.deg], A.c);
        Poly r; poly_from_full(r, buf); return r;
    }
    // 有一般式
    unsigned long long *buf = (unsigned long long*)calloc(MAXD+1, sizeof(unsigned long long));
    if (A.type == 2){
        for (int i = 0; i <= A.deg; ++i) buf[i] = addmod(buf[i], A.arr[i]);
    }else if (A.type == 1){
        buf[A.deg] = addmod(buf[A.deg], A.c);
    }else{
        buf[0] = addmod(buf[0], A.c);
    }
    if (B.type == 2){
        for (int i = 0; i <= B.deg; ++i) buf[i] = addmod(buf[i], B.arr[i]);
    }else if (B.type == 1){
        buf[B.deg] = addmod(buf[B.deg], B.c);
    }else{
        buf[0] = addmod(buf[0], B.c);
    }
    Poly r; poly_from_full(r, buf); return r;
}

static inline Poly poly_sub(const Poly &A, const Poly &B){
    // 常数
    if (A.type == 0 && B.type == 0){
        Poly r; poly_set_const(r, submod(A.c, B.c)); return r;
    }
    // 单项式 - 单项式
    if (A.type == 1 && B.type == 1){
        if (A.deg == B.deg){
            unsigned long long c = submod(A.c, B.c);
            return poly_from_monomial(c, A.deg);
        }else{
            unsigned long long *buf = (unsigned long long*)calloc(MAXD+1, sizeof(unsigned long long));
            buf[A.deg] = addmod(buf[A.deg], A.c);
            buf[B.deg] = addmod(buf[B.deg], (MOD - B.c) % MOD);
            Poly r; poly_from_full(r, buf); return r;
        }
    }
    // 常数/单项式与另一方
    unsigned long long *buf = (unsigned long long*)calloc(MAXD+1, sizeof(unsigned long long));
    if (A.type == 2){
        for (int i = 0; i <= A.deg; ++i) buf[i] = addmod(buf[i], A.arr[i]);
    }else if (A.type == 1){
        buf[A.deg] = addmod(buf[A.deg], A.c);
    }else{
        buf[0] = addmod(buf[0], A.c);
    }
    if (B.type == 2){
        for (int i = 0; i <= B.deg; ++i){
            if (B.arr[i]) buf[i] = submod(buf[i], B.arr[i]);
        }
    }else if (B.type == 1){
        buf[B.deg] = submod(buf[B.deg], B.c);
    }else{
        buf[0] = submod(buf[0], B.c);
    }
    Poly r; poly_from_full(r, buf); return r;
}

static inline Poly poly_mul(const Poly &A, const Poly &B){
    // 0
    if ((A.type == 0 && A.c == 0ULL) || (B.type == 0 && B.c == 0ULL)){
        Poly r; poly_set_const(r, 0ULL); return r;
    }
    // 常数 * 常数
    if (A.type == 0 && B.type == 0){
        Poly r; poly_set_const(r, mulmod(A.c, B.c)); return r;
    }
    // 常数 * 单项式 / 一般式
    if (A.type == 0 && A.c != 0ULL){
        if (B.type == 1){
            return poly_from_monomial(mulmod(A.c, B.c), B.deg);
        }else if (B.type == 2){
            unsigned long long *buf = (unsigned long long*)calloc(MAXD+1, sizeof(unsigned long long));
            for (int i = 0; i <= B.deg; ++i) buf[i] = mulmod(B.arr[i], A.c);
            Poly r; poly_from_full(r, buf); return r;
        }
    }
    if (B.type == 0 && B.c != 0ULL){
        if (A.type == 1){
            return poly_from_monomial(mulmod(B.c, A.c), A.deg);
        }else if (A.type == 2){
            unsigned long long *buf = (unsigned long long*)calloc(MAXD+1, sizeof(unsigned long long));
            for (int i = 0; i <= A.deg; ++i) buf[i] = mulmod(A.arr[i], B.c);
            Poly r; poly_from_full(r, buf); return r;
        }
    }
    // 单项式 * 单项式
    if (A.type == 1 && B.type == 1){
        int d = A.deg + B.deg;
        if (d > MAXD) d = MAXD; 
        return poly_from_monomial(mulmod(A.c, B.c), d);
    }
    // 单项式 * 一般式
    if (A.type == 1 && B.type == 2){
        unsigned long long *buf = (unsigned long long*)calloc(MAXD+1, sizeof(unsigned long long));
        for (int i = 0; i <= B.deg; ++i){
            int k = i + A.deg;
            if (k <= MAXD && B.arr[i]) buf[k] = addmod(buf[k], mulmod(B.arr[i], A.c));
        }
        Poly r; poly_from_full(r, buf); return r;
    }
    if (B.type == 1 && A.type == 2){
        unsigned long long *buf = (unsigned long long*)calloc(MAXD+1, sizeof(unsigned long long));
        for (int i = 0; i <= A.deg; ++i){
            int k = i + B.deg;
            if (k <= MAXD && A.arr[i]) buf[k] = addmod(buf[k], mulmod(A.arr[i], B.c));
        }
        Poly r; poly_from_full(r, buf); return r;
    }
    // 一般式 * 一般式
    unsigned long long *buf = (unsigned long long*)calloc(MAXD+1, sizeof(unsigned long long));
    for (int i = 0; i <= A.deg; ++i){
        if (!A.arr[i]) continue;
        for (int j = 0; j <= B.deg && i + j <= MAXD; ++j){
            if (!B.arr[j]) continue;
            buf[i + j] = addmod(buf[i + j], mulmod(A.arr[i], B.arr[j]));
        }
    }
    Poly r; poly_from_full(r, buf); return r;
}

static inline Poly poly_pow(const Poly &A, unsigned int k){
    // k ≥ 1
    if (k == 1) return poly_clone(A);
    if (A.type == 0){
        Poly r; poly_set_const(r, powmod(A.c, k)); return r;
    }
    if (A.type == 1){
        unsigned long long coef = powmod(A.c, k);
        long long d = (long long)A.deg * (long long)k;
        if (d > MAXD) d = MAXD; // 防御
        return poly_from_monomial(coef, (int)d);
    }
    // 一般式：小幂（k ≤ 4），直接连乘
    Poly res = poly_clone(A);
    for (unsigned int t = 2; t <= k; ++t){
        Poly nxt = poly_mul(res, A);
        poly_release(res);
        res = nxt;
    }
    return res;
}

// --------- 解析与计算 ----------
static inline int precedence(char op){
    if (op == '^') return 3;
    if (op == '*') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int main(){
    // 读取整行（无空格，末尾有 '\n'）
    const int MAXN = 1000005;
    char *s = (char*)malloc(MAXN);
    if (!s) return 0;
    int L = 0, ch;
    while ((ch = getchar()) != EOF && ch != '\n'){
        if (L + 1 < MAXN) s[L++] = (char)ch; // 保护
    }
    s[L] = '\0';
    if (L == 0){ printf("0\n"); free(s); return 0; }

    // 操作符栈与值栈
    char *op = (char*)malloc((L + 5) * sizeof(char));
    Poly *st = (Poly*)malloc((L + 5) * sizeof(Poly));
    int ot = 0, vt = 0;

    enum PrevT { P_NONE, P_NUM, P_X, P_LP, P_RP, P_OP } prev = P_NONE;

    auto apply_top = [&](){
        char o = op[--ot];
        if (o == '+' || o == '-' || o == '*' || o == '^'){
            Poly B = st[--vt];
            Poly A = st[--vt];
            Poly R;
            if (o == '+') R = poly_add(A, B);
            else if (o == '-') R = poly_sub(A, B);
            else if (o == '*') R = poly_mul(A, B);
            else { // '^'
                // 右操作数保证是正整数常数
                unsigned int k = (unsigned int)(B.type == 0 ? B.c : 0ULL);
                if (k == 0U) k = 1U; // 输入保证 k>=1，这里只是防御
                R = poly_pow(A, k);
            }
            poly_release(A);
            poly_release(B);
            st[vt++] = R;
        }
        // '(' 不会到这里
    };

    for (int i = 0; i < L; /*手动控制 i*/){
        char c = s[i];

        // —— 省略乘号的注入 —— 
        if (c == '('){
            if (prev == P_NUM || prev == P_X || prev == P_RP){
                // 先处理一个 '*'
                while (ot > 0 && op[ot-1] != '(' && precedence(op[ot-1]) >= precedence('*')) apply_top();
                op[ot++] = '*';
                prev = P_OP;
                continue; // 继续处理当前 '('
            }
        }else if (c == 'x'){
            if ((prev == P_NUM || prev == P_RP)){ // 左侧不是 x 才可省略
                while (ot > 0 && op[ot-1] != '(' && precedence(op[ot-1]) >= precedence('*')) apply_top();
                op[ot++] = '*';
                prev = P_OP;
                continue; // 继续处理当前 'x'
            }
        }

        if (c == 'x'){
            Poly px; poly_set_x(px);
            st[vt++] = px;
            prev = P_X;
            ++i;
        }else if (isdigit((unsigned char)c)){
            // 读一个正整数字面量
            unsigned long long val = 0ULL;
            while (i < L && isdigit((unsigned char)s[i])){
                val = (val * 10ULL + (unsigned long long)(s[i]-'0')) % MOD;
                ++i;
            }
            Poly pc; poly_set_const(pc, val);
            st[vt++] = pc;
            prev = P_NUM;
        }else if (c == '+' || c == '-' || c == '*' || c == '^'){
            // 出栈（左结合：>=）
            while (ot > 0 && op[ot-1] != '(' && precedence(op[ot-1]) >= precedence(c)) apply_top();
            op[ot++] = c;
            prev = P_OP;
            ++i;
        }else if (c == '('){
            op[ot++] = c;
            prev = P_LP;
            ++i;
        }else if (c == ')'){
            while (ot > 0 && op[ot-1] != '(') apply_top();
            if (ot > 0 && op[ot-1] == '(') --ot; // 弹出 '('
            prev = P_RP;
            ++i;
        }else{
            ++i;
        }
    }
    while (ot > 0) apply_top();

    // 结果在 st[vt-1]
    Poly res = st[vt-1];

    // 规范输出
    if (res.type == 0){
        if (res.c == 0ULL){
            printf("0\n");
        }else{
            printf("%llu\n", res.c);
        }
    }else if (res.type == 1){
        if (res.c == 0ULL){
            printf("0\n");
        }else{
            int d = res.deg;
            // 去除前导 0（单项式不会有）
            // 输出从最高次到常数
            // 最高项系数
            printf("%llu", res.c);
            for (int k = d - 1; k >= 1; --k) printf(" 0");
            printf(" 0\n"); // 常数项
        }
    }else{ // 一般式
        // 去前导 0
        int d = res.deg;
        while (d > 0 && res.arr[d] == 0ULL) --d;
        if (d == 0 && res.arr[0] == 0ULL){
            printf("0\n");
        }else{
            for (int k = d; k >= 0; --k){
                if (k != d) printf(" ");
                printf("%llu", res.arr[k]);
            }
            printf("\n");
        }
    }

    // 释放内存
    poly_release(res);
    free(op);
    free(st);
    free(s);
    return 0;
}
