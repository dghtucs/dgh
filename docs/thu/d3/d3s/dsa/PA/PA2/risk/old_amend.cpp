#include <cstdio>  // 替换 iostream，用 scanf/printf 避免溢出和效率问题
using namespace std;

const int MAX_N = 1000000 + 5;
const int MAX_XI = 2000000 + 5;

int n, T;
int xi[MAX_N];       // 确诊病例数，xi[1..n]（xi[0] 无用）
unsigned int mi[MAX_N];  // m_i 可能超 int，用 unsigned int
int k[MAX_N];        // 每天的最大值 k[1..n]
int cnt[MAX_XI] = {0};   // 初始化必须为0（全局数组默认0，但显式初始化更安全）
int sum[MAX_XI] = {0};   // 前缀和数组

// 双端队列（修正 push 方法冗余）
class Deque {
private:
    int value[MAX_N];   // 存储 xi 值（最大值2e6，int足够）
    unsigned int index[MAX_N];  // 索引可能超 int，用 unsigned int
    int front, back;

public:
    Deque() : front(0), back(0) {}
    void clear() { front = back = 0; }
    bool empty() const { return front == back; }
    
    // 修正：push 方法已包含移除队尾小于当前值的逻辑，无需在 main 中重复
    void push(int val, unsigned int idx) {
        while (back > front && value[back - 1] <= val) {
            back--;
        }
        value[back] = val;
        index[back] = idx;
        back++;
    }
    
    void pop_front() { if (front < back) front++; }
    int get_max() const { return empty() ? 0 : value[front]; }
    unsigned int get_front_index() const { return empty() ? 0 : index[front]; }
    int get_back_value() const { return value[back - 1]; }
    unsigned int get_back_index() const { return index[back - 1]; }
    void pop_back() { if (back > front) back--; }
};

int main() {
    // 用 scanf 读取，避免 cin 的溢出和效率问题
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &xi[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%u", &mi[i]);  // 读取 unsigned int
    }

    // 计算每一天的最大值 k[i]（修正重复移除队尾元素）
    Deque dq;
    for (int i = 1; i <= n; i++) {
        // 移除超出窗口的元素：窗口左边界是 i - mi[i]，索引 < 左边界的出队
        unsigned int left = i - mi[i];
        while (!dq.empty() && dq.get_front_index() < left) {
            dq.pop_front();
        }

        // 插入 xi[i-1]
        int val = (i == 1) ? 0 : xi[i - 1];  // 第1天追溯前0天，val=0（xi[0]无需定义）
        unsigned int idx = i - 1;
        dq.push(val, idx);

        // 记录 k[i] 并统计
        k[i] = dq.get_max();
        if (k[i] < MAX_XI) {  // 避免 k[i] 超界（题目中 k[i] <=2e6，此判断保险）
            cnt[k[i]]++;
        }
    }

    // 构建前缀和数组（逻辑正确，但需确保 cnt 初始化为0）
    sum[0] = cnt[0];
    for (int i = 1; i < MAX_XI; i++) {
        sum[i] = sum[i - 1] + cnt[i];
    }

    // 处理查询（修正 q-1 >= MAX_XI 时的计算）
    scanf("%d", &T);
    while (T--) {
        unsigned int p, q;
        scanf("%u%u", &p, &q);

        int lowRisk = 0, midRisk = 0;

        // 低风险：k < p → 即 k <= p-1
        if (p > 0) {
            if (p - 1 >= MAX_XI) {
                lowRisk = sum[MAX_XI - 1];  // 所有 k 都 <= p-1
            } else {
                lowRisk = sum[p - 1];
            }
        } else {
            lowRisk = 0;  // p=0 时，k <0 不可能
        }

        // 中风险：p <= k < q → 即 k <= q-1 且 k >=p → sum[q-1] - sum[p-1]
        if (q > 0) {
            int sum_q = (q - 1 >= MAX_XI) ? sum[MAX_XI - 1] : sum[q - 1];
            midRisk = sum_q - lowRisk;
        } else {
            midRisk = 0;  // q=0 时，k <0 不可能
        }

        printf("%d %d\n", lowRisk, midRisk);
    }

    return 0;
}