#include <bits/stdc++.h>
const int maxn = 200;
const int inf = 0x3f3f3f3f;
using namespace std;

int N,dis[maxn][maxn],vis[maxn],ans,mndis[maxn];

void prim(){
    //��ʼ������1�ŵ���뵽��������
    ans = 0;
    int cnt = 1;
    vis[1] = 1;
    for(int i = 1;i <= N;++i) mndis[i]=dis[1][i];
    while(cnt != N){
        int mn = inf,id;
        //�ҳ����е��о�������������ĵ�
        for(int i = 1; i <= N; i++){
            if(!vis[i] && mndis[i] < mn){
                mn = mndis[i];
                id = i;
            }
        }
        //���ҵ��ĵ����������
        vis[id] = 1;
        ans += mn;
        cnt++;
        //����ʣ��㵽���ľ���
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
