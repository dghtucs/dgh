#include <cstdio>
#include <cstdlib>

typedef long long ll;

// 常量定义
const int MAX_N = 1000000 + 10;    // 最大天数
const int MAX_K = 2000000 + 10;    // x_i <= 2e6
const int MAX_QUEUE_SIZE = MAX_N;  // 队列最大长度

// 双端队列类（替代STL deque）
class Deque {
private:
    ll data[MAX_QUEUE_SIZE];
    int front_, rear_;
public:
    Deque() : front_(0), rear_(-1) {}
    void push_back(ll val) { data[++rear_] = val; }
    void pop_front() { if (!empty()) front_++; }
    void pop_back() { if (!empty()) rear_--; }
    ll front() const { return data[front_]; }
    ll back() const { return data[rear_]; }
    bool empty() const { return front_ > rear_; }
    void clear() { front_ = 0; rear_ = -1; }
};

// 全局数据（避免栈溢出，访问高效）
ll x[MAX_N];          // 每日确诊数
ll m_list[MAX_N];     // 每日追溯天数
ll k[MAX_N];          // 每日窗口最大值
int cnt[MAX_K] = {0}; // 最大值计数数组
int prefix[MAX_K] = {0}; // 前缀和数组

// 查询结果存储
int res_low[MAX_N];
int res_mid[MAX_N];

int main() {
    // 1. 读取输入
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &x[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &m_list[i]);
    }
    int T;
    scanf("%d", &T);
    ll *p = new ll[T];
    ll *q = new ll[T];
    for (int i = 0; i < T; i++) {
        scanf("%lld%lld", &p[i], &q[i]);
    }

    // 2. 用Max Queue计算每日窗口最大值k数组
    Deque val_queue, idx_queue, max_deque;
    ll current_idx = 0;

    for (int i = 0; i < n; i++) {
        ll L = i - m_list[i];
        ll current_x = (i == 0) ? 0 : x[i - 1];

        // 入队
        val_queue.push_back(current_x);
        idx_queue.push_back(current_idx++);

        // 维护单调递减队列
        while (!max_deque.empty() && max_deque.back() < current_x) {
            max_deque.pop_back();
        }
        max_deque.push_back(current_x);

        // 移除窗口外元素
        while (!idx_queue.empty() && idx_queue.front() < L) {
            ll out_val = val_queue.front();
            val_queue.pop_front();
            idx_queue.pop_front();
            if (out_val == max_deque.front()) {
                max_deque.pop_front();
            }
        }

        // 记录最大值
        k[i] = max_deque.empty() ? 0 : max_deque.front();
    }

    // 3. 统计频次与前缀和
    for (int i = 0; i < n; i++) {
        if (k[i] < MAX_K) {
            cnt[(int)k[i]]++;
        }
    }
    prefix[0] = 0;
    for (int s = 1; s < MAX_K; s++) {
        prefix[s] = prefix[s - 1] + cnt[s - 1];
    }

    // 4. 处理查询
    for (int i = 0; i < T; i++) {
        ll pi = p[i], qi = q[i];
        int low = 0;
        if (pi > 0) {
            ll bound = (pi - 1) < (MAX_K - 2) ? (pi - 1) : (MAX_K - 2);
            low = prefix[(int)bound];
        }
        ll q_bound = (qi - 1) < (MAX_K - 2) ? (qi - 1) : (MAX_K - 2);
        int mid = prefix[(int)q_bound] - low;
        res_low[i] = low;
        res_mid[i] = mid;
    }

    // 5. 输出结果
    for (int i = 0; i < T; i++) {
        printf("%d %d\n", res_low[i], res_mid[i]);
    }

    // 释放动态内存
    delete[] p;
    delete[] q;

    return 0;
}