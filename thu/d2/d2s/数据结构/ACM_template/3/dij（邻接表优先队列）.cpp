#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
const int maxn = 1000+50;
const int inf = 0x3f3f3f3f;
using namespace std;
struct edge{
    int to;
    int val;
    edge(int a = 0,int b = 0){to=a;val=b;}
};
struct nod{
    int pos;
    int d;
    nod(int a = 0,int b = 0){pos=a;d=b;}
    //优先队列重载大于符号
    friend bool operator > (nod a, nod b){
        return a.d>b.d;
    }
};
//邻接表
vector<edge> E[maxn];

int T,N,dis[maxn];//dis[i]为从X到i的最短距离，可以根据情况扩充为d[i][j][k].....

//加边，无向图时添加两条边
void add(int f,int t,int v){
    E[f].push_back(edge(t,v));
    E[t].push_back(edge(f,v));
    return;
}

void dij(){
    memset(dis,inf,sizeof(dis));
    priority_queue< nod,vector<nod>,greater<nod> > Q;
    dis[N]=0;
    Q.push(nod(N,0));//初始态,N为出发点
    while(!Q.empty()){
        nod temp = Q.top();
        int pos = temp.pos;
        int d = temp.d;
        Q.pop();
        if(d > dis[pos]) continue;
        //遍历邻接表更新相邻点的最短距离
        for(int i = 0; i < E[pos].size(); ++i){
            int to = E[pos][i].to;
            int val = E[pos][i].val;
            int nd = d + val;
            if(nd < dis[to]){
                dis[to] = nd;
                Q.push(nod(to,nd));
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> T >> N;
    while(T--){
        int from,to,val;
        cin >> from >> to >> val;
        add(from,to,val);
    }
    dij();
    cout << dis[1] << endl;
    return 0;
}
