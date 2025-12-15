#include <cstdio>
#include <cstring>

static const int MAXN = 100000;     // N <= 1e5
static const int MAXM = 100000;     // M <= 1e5
static const long long INF = 1000000000000000000LL; // 足够大的无穷

// 图的存储：链式前向星
// 对于无向图，每条边 (u,v) 要存两次
int head[MAXN+5], nxt[2*MAXM+5], to[2*MAXM+5];
int edge_count = 0;

// 插入边 (u -> v)
void add_edge(int u, int v){
    // edge_count 从 0 开始
    // nxt[edge_count] = head[u], head[u] = edge_count, to[edge_count] = v
    nxt[edge_count] = head[u];
    to[edge_count] = v;
    head[u] = edge_count++;
}

// 小根堆（手写）的元素
struct HeapNode {
    long long dist; // 当前距离
    int node;       // 节点编号
};

// 二叉堆数组
static HeapNode heap[ MAXN+5 ];
int heap_size = 0;

// 向上调整
void sift_up(int idx){
    while(idx > 1){
        int parent = idx >> 1;
        if(heap[parent].dist <= heap[idx].dist) break;
        // swap
        HeapNode tmp = heap[parent];
        heap[parent] = heap[idx];
        heap[idx] = tmp;
        idx = parent;
    }
}

// 向下调整
void sift_down(int idx){
    while(true){
        int left = idx<<1, right = left+1;
        int smallest = idx;
        if(left <= heap_size && heap[left].dist < heap[smallest].dist){
            smallest = left;
        }
        if(right <= heap_size && heap[right].dist < heap[smallest].dist){
            smallest = right;
        }
        if(smallest == idx) break;
        // swap
        HeapNode tmp = heap[idx];
        heap[idx] = heap[smallest];
        heap[smallest] = tmp;
        idx = smallest;
    }
}

// push
void heap_push(long long dist, int node){
    heap_size++;
    heap[heap_size].dist = dist;
    heap[heap_size].node = node;
    sift_up(heap_size);
}

// pop
HeapNode heap_pop(){
    HeapNode ret = heap[1];
    heap[1] = heap[heap_size];
    heap_size--;
    sift_down(1);
    return ret;
}

// 全局数据
long long dist[MAXN+5];  // dist[i] 表示从 1 到 i 的最短通关代价
long long ways[MAXN+5];  // ways[i] 表示达到 dist[i] 的路径数
long long cost[MAXN+5];  // cost[i] 表示关卡 i 的通关时间 T[i]
static const long long MOD = 1000000007;

int main(){
    // 读入 N, M
    int N, M;
    std::scanf("%d %d", &N, &M);

    // 读入每个关卡的时间 cost[i]
    for(int i=1; i<=N; i++){
        std::scanf("%lld", &cost[i]);
    }

    // 初始化 head = -1 表示无边
    for(int i=1; i<=N; i++){
        head[i] = -1;
    }
    edge_count = 0;

    // 读入 M 条边 (无向)
    for(int i=0; i<M; i++){
        int u, v;
        std::scanf("%d %d", &u, &v);
        // 建立无向边 => add_edge(u,v) && add_edge(v,u)
        add_edge(u,v);
        add_edge(v,u);
    }

    // Dijkstra 初始化
    for(int i=1; i<=N; i++){
        dist[i] = INF;
        ways[i] = 0;
    }
    dist[1] = cost[1];  // 从起点1开始，初始代价为 cost[1]
    ways[1] = 1;        // 路径数为 1
    heap_size = 0;
    heap_push(dist[1], 1);

    // Dijkstra
    while(heap_size > 0){
        HeapNode top = heap_pop();
        long long curD = top.dist;
        int u = top.node;
        // 检查是否是“过期”堆节点
        if(curD > dist[u]) continue;
        // 遍历 u 的邻居
        for(int e = head[u]; e != -1; e = nxt[e]){
            int v = to[e];
            long long nd = dist[u] + cost[v];
            if(nd < dist[v]){
                dist[v] = nd;
                ways[v] = ways[u];
                heap_push(nd, v);
            } else if(nd == dist[v]){
                ways[v] = (ways[v] + ways[u]) % MOD;
            }
        }
    }

    // 输出结果：第一行是 dist[N]，第二行是 ways[N] mod 1e9+7
    // 保证 1..N 连通，dist[N]不会是 INF
    std::printf("%lld\n", dist[N]);
    std::printf("%lld\n", ways[N] % MOD);

    return 0;
}
