#include <iostream>
using namespace std;

const int MAX_N = 1000000 + 5;
const int MAX_XI = 2000000 + 5;

int n, T;
int xi[MAX_N];       // 确诊病例数，xi[0..n]
int mi[MAX_N];       // 每天的 mi 值
int k[MAX_N];        // 每天的最大值 k[i]
int cnt[MAX_XI];     // 计数每个可能的 k[i] 值出现的次数
int sum[MAX_XI];     // 前缀和，用于快速计算区间内的天数

// 双端口队列
class Deque {
private:
    int value[MAX_N];   // 存储 xi 值
    int index[MAX_N];   // 存储对应的索引
    int front, back;

public:
    Deque() : front(0), back(0) {}
    //清空
    void clear() {
        front = back = 0;
    }

    bool empty() const {
        return front == back;
    }
    //输入元素
    void push(int val, int idx) {
        while (back > front && value[back - 1] <= val) {
            back--;
        }
        value[back] = val;
        index[back] = idx;
        back++;
    }
    //前部pop
    void pop_front() {
        if (front < back) {
            front++;
        }
    }

    int get_max() const {
        return empty() ? 0 : value[front];
    }

    int get_front_index() const {
        return empty() ? -1 : index[front];
    }

    int get_back_value() const {
        return value[back - 1];
    }

    int get_back_index() const {
        return index[back - 1];
    }

    void pop_back() {
        if (back > front) {
            back--;
        }
    }
};

int main() {
    // 加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 输入 xi[1..n]
    for (int i = 1; i <= n; i++) {
        cin >> xi[i];
    }

    xi[0] = 0;  // xi[0] 定义为 0

    // 输入 mi[1..n]
    for (int i = 1; i <= n; i++) {
        cin >> mi[i];
    }

    // 计算每一天的最大值 k[i]
    Deque dq;
    for (int i = 1; i <= n; i++) {
        // 移除超出窗口的元素
        while (!dq.empty() && dq.get_front_index() < i - mi[i]) {
            dq.pop_front();
        }

        // 插入 xi[i - 1]
        int val = xi[i - 1];
        int idx = i - 1;

        while (!dq.empty() && dq.get_back_value() <= val) {
            dq.pop_back();
        }
        dq.push(val, idx);

        // 记录当天的最大值 k[i]
        k[i] = dq.get_max();
        // 统计每个可能的 k[i]
        cnt[k[i]]++;
    }

    // 构建前缀和数组 sum[k]
    sum[0] = cnt[0];
    for (int i = 1; i < MAX_XI; i++) {
        sum[i] = sum[i - 1] + cnt[i];
    }

    int total_days = n;
    int max_k = 2000000;  // 最大可能的 k[i] 值

    // 读取 T 组查询
    cin >> T;
    for (int t = 0; t < T; t++) {
        unsigned int p, q;
        cin >> p >> q;

        int lowRisk = 0, midRisk = 0;

        // 处理 lowRisk
        if (p == 0) {
            lowRisk = 0;
        } else if (p - 1 >= MAX_XI) {
            lowRisk = total_days;
        } else {
            lowRisk = sum[p - 1];
        }

        // 处理 midRisk
        if (q == 0) {
            midRisk = 0;
        } else if (q - 1 >= MAX_XI) {
            midRisk = total_days - lowRisk;
        } else {
            midRisk = sum[q - 1] - lowRisk;
        }

        cout << lowRisk << " " << midRisk << "\n";//输出 lowRisk 和 midRisk
    }

    return 0;
}
