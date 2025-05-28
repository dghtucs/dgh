#include <bits/stdc++.h>
const int maxn = 200;
const int inf = 0x3f3f3f3f;
using namespace std;

int N,dis[maxn][maxn],vis[maxn],ans,mndis[maxn];

void prim(){
    //初始化，将1号点加入到生成树中
    ans = 0;
    int cnt = 1;
    vis[1] = 1;
    for(int i = 1;i <= N;++i) mndis[i]=dis[1][i];
    while(cnt != N){
        int mn = inf,id;
        //找出所有点中距离生成树最近的点
        for(int i = 1; i <= N; i++){
            if(!vis[i] && mndis[i] < mn){
                mn = mndis[i];
                id = i;
            }
        }
        //将找到的点加入生成树
        vis[id] = 1;
        ans += mn;
        cnt++;
        //更新剩余点到树的距离
        for(int i = 1; i <= N; i++) mndis[i] = min(mndis[i],dis[id][i]);

    }
}


int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    while(cin >> N){
        if(!N) break;
        memset(dis,0,sizeof(dis));
        memset(vis,0,sizeof(vis));
        int T = N * (N - 1) / 2;
        while(T--){
            int a,b,c;
            cin >> a >> b >> c;
            dis[a][b] = dis[b][a] = c;
        }
        prim();
        cout << ans << endl;
    }
    return 0;
}
