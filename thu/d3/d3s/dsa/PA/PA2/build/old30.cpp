#include <cstdio>
#include <cstring>

const int MAXN = 1000000 + 5;  // 最大节点数量
const int MAXM = 10000 + 5;    // 最大操作数量
const int MAXCOST = 1000000;   // 最大总成本

int N, M;
int total_cost = 0;

int parent[MAXN];         // 每个节点的父节点
int first_child[MAXN];    // 每个节点的第一个子节点
int next_sibling[MAXN];   // 每个节点的下一个兄弟节点
int size[MAXN];           // 以每个节点为根的子树规模
int height[MAXN];         // 以每个节点为根的子树高度
int depth[MAXN];          // 每个节点的深度
int tin[MAXN];            // 节点的进入时间戳
int tout[MAXN];           // 节点的离开时间戳
int timer = 0;            // 全局时间戳计数器

// 函数：递归计算每个节点的规模、高度、深度，并初始化时间戳
void computeSizeHeight(int node, int dep) {
    size[node] = 1;
    height[node] = 0;
    depth[node] = dep;
    tin[node] = ++timer;  // 进入节点，时间戳加一
    int child = first_child[node];
    while (child != 0) {
        computeSizeHeight(child, dep + 1);
        size[node] += size[child];
        if (height[child] + 1 > height[node]) {
            height[node] = height[child] + 1;
        }
        child = next_sibling[child];
    }
    tout[node] = ++timer;  // 离开节点，时间戳加一
}

// 函数：读取通路表示法，返回对应的节点编号
int getNodeByPath() {
    int m;
    scanf("%d", &m);
    total_cost += m;
    int node = 1;  // 从根节点开始
    for (int i = 0; i < m; i++) {
        int rank;
        scanf("%d", &rank);
        total_cost += rank;
        int child = first_child[node];
        int cnt = 0;
        while (child != 0 && cnt < rank) {
            child = next_sibling[child];
            cnt++;
        }
        if (child == 0) {
            break;  // 无效的排行，返回当前节点
        }
        node = child;
    }
    return node;
}

// 函数：检查节点 d 是否在以节点 s 为根的子树中，防止形成环
bool isDescendant(int s, int d) {
    // 使用时间戳判断
    return tin[s] <= tin[d] && tout[d] <= tout[s];
}

// 函数：更新节点 u 的规模和高度
void updateSizeHeight(int u) {
    int child = first_child[u];
    size[u] = 1;
    int max_child_height = 0;
    while (child != 0) {
        size[u] += size[child];
        if (height[child] + 1 > max_child_height) {
            max_child_height = height[child] + 1;
        }
        child = next_sibling[child];
    }
    height[u] = max_child_height;
    // 递归更新父节点
    if (u != 1) {
        updateSizeHeight(parent[u]);
    }
}

// 函数：更新子树 s 中所有节点的深度和时间戳
void updateDepthAndTimestamp(int s, int delta_depth) {
    static int stack[MAXN];
    int top = 0;
    timer++;  // 每次更新子树时，时间戳自增，避免冲突
    stack[top++] = s;
    depth[s] += delta_depth;
    tin[s] = ++timer;
    int child = first_child[s];
    while (top > 0) {
        int node = stack[--top];
        child = first_child[node];
        while (child != 0) {
            depth[child] += delta_depth;
            tin[child] = ++timer;
            stack[top++] = child;
            child = next_sibling[child];
        }
        tout[node] = ++timer;
    }
}

// 函数：在移动操作中，重新计算时间戳
void reassignTimestamp(int node) {
    tin[node] = ++timer;
    int child = first_child[node];
    while (child != 0) {
        reassignTimestamp(child);
        child = next_sibling[child];
    }
    tout[node] = ++timer;
}

int main() {
    // 读取 N 和 M
    scanf("%d %d", &N, &M);

    // 初始化数组
    memset(parent, 0, sizeof(parent));
    memset(first_child, 0, sizeof(first_child));
    memset(next_sibling, 0, sizeof(next_sibling));

    // 构建初始树
    for (int i = 1; i <= N; i++) {
        int di;
        scanf("%d", &di);
        int last_child = 0;
        for (int j = 0; j < di; j++) {
            int c;
            scanf("%d", &c);
            parent[c] = i;
            if (first_child[i] == 0) {
                first_child[i] = c;
            } else {
                next_sibling[last_child] = c;
            }
            last_child = c;
        }
    }

    // 计算初始规模、高度、深度和时间戳
    timer = 0;
    computeSizeHeight(1, 1);

    // 处理 M 个操作
    for (int op_idx = 0; op_idx < M; op_idx++) {
        int op_type;
        scanf("%d", &op_type);
        if (op_type == 0) {
            // 移动操作
            int s = getNodeByPath();  // 源子树根节点 s
            int d = getNodeByPath();  // 目标节点 d
            int k;
            scanf("%d", &k);
            total_cost += k;

            // 检查总成本
            if (total_cost > MAXCOST) {
                return 0;  // 超过总成本限制，不输出结果
            }

            // 防止形成环
            if (isDescendant(s, d)) {
                continue;  // 跳过此次移动
            }

            // 从旧父节点中移除 s
            int old_parent = parent[s];
            if (old_parent != 0) {
                if (first_child[old_parent] == s) {
                    first_child[old_parent] = next_sibling[s];
                } else {
                    int prev = first_child[old_parent];
                    while (prev != 0 && next_sibling[prev] != s) {
                        prev = next_sibling[prev];
                    }
                    if (prev != 0) {
                        next_sibling[prev] = next_sibling[s];
                    }
                }
                parent[s] = 0;
                next_sibling[s] = 0;

                // 更新旧父节点的规模和高度
                updateSizeHeight(old_parent);
            }

            // 计算 d 的子节点数量
            int num_children_d = 0;
            int temp_child = first_child[d];
            while (temp_child != 0) {
                num_children_d++;
                temp_child = next_sibling[temp_child];
            }

            // 调整 k，如果超过子节点数量，则插入到末尾
            if (k > num_children_d) {
                k = num_children_d;
            }

            // 将 s 插入到 d 的孩子列表的第 k 位
            if (k == 0) {
                next_sibling[s] = first_child[d];
                first_child[d] = s;
            } else {
                int curr = first_child[d];
                int prev = 0;
                int cnt = 0;
                while (curr != 0 && cnt < k) {
                    prev = curr;
                    curr = next_sibling[curr];
                    cnt++;
                }
                next_sibling[s] = curr;
                next_sibling[prev] = s;
            }
            parent[s] = d;

            // 更新 s 中所有节点的深度和时间戳
            int delta_depth = depth[d] + 1 - depth[s];
            updateDepthAndTimestamp(s, delta_depth);

            // 更新新父节点 d 的规模和高度
            updateSizeHeight(d);

        } else if (op_type == 1) {
            // 高度查询
            int s = getNodeByPath();
            // 检查总成本
            if (total_cost > MAXCOST) {
                return 0;  // 超过总成本限制，不输出结果
            }
            printf("%d\n", height[s]);
        } else if (op_type == 2) {
            // 规模查询
            int s = getNodeByPath();
            // 检查总成本
            if (total_cost > MAXCOST) {
                return 0;  // 超过总成本限制，不输出结果
            }
            printf("%d\n", size[s]);
        }
    }

    return 0;
}
