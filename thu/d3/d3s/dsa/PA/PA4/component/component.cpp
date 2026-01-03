#include <cstdio>
#include <cstring>

// ========== 并查集部分 ==========

static const int MAXN = 1000000;

// 并查集数组
int fa[MAXN+5];    // 父节点
int rankv[MAXN+5]; // rank(用于按秩合并)

// 并查集初始化
void uf_init(int n) {
    for(int i = 1; i <= n; i++){
        fa[i] = i;
        rankv[i] = 0;
    }
}

// 并查集找根
int uf_find(int x){
    if(fa[x] == x) return x;
    fa[x] = uf_find(fa[x]);
    return fa[x];
}

// 并查集合并
int uf_union(int x, int y) {
    // 返回新的根
    x = uf_find(x);
    y = uf_find(y);
    if(x == y) return x; // 已在同一连通分量

    if(rankv[x] < rankv[y]) {
        fa[x] = y;
        return y;
    } else if(rankv[x] > rankv[y]) {
        fa[y] = x;
        return x;
    } else {
        fa[y] = x;
        rankv[x]++;
        return x;
    }
}

// ========== 左式堆(可并堆)部分 ==========
// 用来维护“前 k 大”的权值集合

// 为简化，令MAXK=某个较小值，若 k 巨大仍需特殊优化
static const int MAXK = 100; 

// 对每个节点(连通分量的根)，存储一个堆结点指针
// 但实际上，每个连通分量的左式堆并非只挂在根节点——只在“并查集根”处保存它

// 堆结点结构
struct HeapNode {
    long long val;
    HeapNode* left;
    HeapNode* right;
    int size;
    int dist; // 左式堆中用于维护距离(零路径长)
};

// 给每个并查集根一个指针
HeapNode* heapRoot[MAXN+5];

// 手写一个简易的静态池来分配堆结点 (不使用 new/delete)
static HeapNode nodePool[2*MAXN+5]; // 视数据规模可能需要更大
int nodePoolTop = 0;

// 分配一个堆结点
HeapNode* newNode(long long v){
    HeapNode* p = &nodePool[nodePoolTop++];
    p->val = v;
    p->left = p->right = NULL;
    p->dist = 0;
    p->size = 1;
    return p;
}

// 合并两个左式堆
HeapNode* mergeHeap(HeapNode* a, HeapNode* b){
    if(!a) return b;
    if(!b) return a;
    // 若a->val < b->val, 则交换, 使得a始终是值更大的
    if(a->val > b->val){
        HeapNode* tmp = a; a=b; b=tmp;
    }
    // 把b合并到a->right
    a->right = mergeHeap(a->right, b);
    // 左式堆保持左儿子的零路径长 >= 右儿子的零路径长
    if(!a->left || (a->left->dist < a->right->dist)){
        // swap
        HeapNode* tmp = a->left;
        a->left = a->right;
        a->right = tmp;
    }
    // dist = right子树的dist +1
    if(a->right == NULL) a->dist = 0;
    else a->dist = a->right->dist + 1;
    a->size = 1;
    if(a->left != NULL) a->size += a->left->size;
    if(a->right != NULL) a->size += a->right->size;
    // a->size = a->left->size + a->right->size + 1;
    return a;
}

// 向左式堆插入一个值
HeapNode* insertHeap(HeapNode* root, long long v){
    HeapNode* node = newNode(v);
    return mergeHeap(root, node);
}

// 只保留前k大的值 -> 插入后若size超过k，则弹出最小值

// 统计“堆中元素总数”并“只保留前k大”的粗略做法(需要遍历堆+合并小的分支? 下面演示简单处理)
static int tmpStackPos;
static HeapNode* stackNodes[3000005]; // 存放遍历用

void collectAll(HeapNode* r){
    // 将堆的所有节点压栈
    if(!r) return;
    stackNodes[tmpStackPos++] = r;
    collectAll(r->left);
    collectAll(r->right);
}

// 合并两个并查集根对应的堆，返回合并后新的堆根
HeapNode* unionHeap(HeapNode* h1, HeapNode* h2, int k){
    // 首先合并成一个堆
    HeapNode* merged = mergeHeap(h1, h2);
    while(merged->size > k)
    {
        merged = mergeHeap(merged->left,merged->right);
    }

    // // 然后把堆里所有元素取出来，并只保留前k大
    // tmpStackPos = 0;
    // collectAll(merged);
    // // 清空 merged
    // merged = NULL;

    // // 简单选择排序or partition找前k大(注意不能用STL sort)
    // // 这里演示一个O(K* size)的简单做法(若k很大会超时，需要更优算法):
    // int total = tmpStackPos;
    // // 将stackNodes里按val冒泡取前k大
    // // 只演示思路，不保证高效
    // for(int i = 0; i < k && i < total; i++){
    //     // 第i大的放到下标i
    //     for(int j = i+1; j < total; j++){
    //         if(stackNodes[j]->val > stackNodes[i]->val){
    //             HeapNode* tmp = stackNodes[j];
    //             stackNodes[j] = stackNodes[i];
    //             stackNodes[i] = tmp;
    //         }
    //     }
    // }
    // // 取前k个做成一个左式堆
    // int limit = (k < total ? k : total);
    // for(int i = 0; i < limit; i++){
    //     stackNodes[i]->left = stackNodes[i]->right = NULL;
    //     stackNodes[i]->dist = 0;
    // }
    // merged = NULL;

    // for(int i=0; i<limit; i++){
    //     merged = mergeHeap(merged, stackNodes[i]);
    // }
    // // 剩下的就丢弃了(因为只需要前k大)
    return merged;
}

// 查询：把堆root的所有节点遍历相加(仅当其数量>=k，否则-1)
long long sumOfHeap(HeapNode* r, int k){
    // 遍历堆中所有节点
    tmpStackPos = 0;
    // collectAll(r);
    int total = tmpStackPos;
    if(r->size < k) return -1; // 不足k个
    else
        return r->val;
    // // 取前k大的值(因这个堆实际上只存了前k大，但仍需遍历确认个数)
    // long long s = 0;
    // // 这里堆中存的已经是前k大的了(若严格维护) -> 直接把全部加起来?
    // // 若保险起见，仍做一次选择k大
    // // 下面为简单演示:
    // // 冒泡找最大的k个
    // for(int i = 0; i < k; i++){
    //     for(int j = i+1; j < total; j++){
    //         if(stackNodes[j]->val > stackNodes[i]->val){
    //             HeapNode* tmp = stackNodes[j];
    //             stackNodes[j] = stackNodes[i];
    //             stackNodes[i] = tmp;
    //         }
    //     }
    //     s += stackNodes[i]->val;
    // }
    // return stackNodes[k-1]->val;
}

// ========== 主流程 ==========

// 节点权值
long long weight[MAXN+5];

int main(){
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    // 读入 n, m, k, q
    int n, m, K, q;
    std::scanf("%d %d %d %d", &n, &m, &K, &q);

    // 读入 n 个点权
    for(int i = 1; i <= n; i++){
        std::scanf("%lld", &weight[i]);
    }

    // 初始化并查集 & 堆指针
    uf_init(n);
    for(int i=1; i<=n; i++){
        heapRoot[i] = newNode(weight[i]);
    }

    // 读入原图的 m 条边
    for(int i=0; i<m; i++){
        int u,v;
        std::scanf("%d %d", &u, &v);
        // union
        int r1 = uf_find(u);
        int r2 = uf_find(v);
        if(r1 != r2){
            int r = uf_union(r1, r2);
            // merge heap
            if(r == r1){
                heapRoot[r1] = unionHeap(heapRoot[r1], heapRoot[r2], K);
            } else {
                heapRoot[r] = unionHeap(heapRoot[r1], heapRoot[r2], K);
            }
        }
    }

    // 处理 q 次操作
    while(q--){
        int op;
        std::scanf("%d",&op);
        if(op == 1){
            // 加边
            int u,v;
            std::scanf("%d %d",&u,&v);
            int r1 = uf_find(u);
            int r2 = uf_find(v);
            if(r1 != r2){
                int r = uf_union(r1, r2);
                // 合并堆
                if(r == r1){
                    heapRoot[r1] = unionHeap(heapRoot[r1], heapRoot[r2], K);
                } else {
                    heapRoot[r] = unionHeap(heapRoot[r1], heapRoot[r2], K);
                }
            }
        } else {
            // 查询：给定u，取其所在分量的前k大和
            int u;
            std::scanf("%d",&u);
            int r = uf_find(u);
            long long ans = sumOfHeap(heapRoot[r], K);
            std::printf("%lld\n", ans);
        }
    }

    return 0;
}
