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
    //���ȶ������ش��ڷ���
    friend bool operator > (nod a, nod b){
        return a.d>b.d;
    }
};
//�ڽӱ�
vector<edge> E[maxn];

int T,N,dis[maxn];//dis[i]Ϊ��X��i����̾��룬���Ը����������Ϊd[i][j][k].....

//�ӱߣ�����ͼʱ���������
void add(int f,int t,int v){
    E[f].push_back(edge(t,v));
    E[t].push_back(edge(f,v));
    return;
}

void dij(){
    memset(dis,inf,sizeof(dis));
    priority_queue< nod,vector<nod>,greater<nod> > Q;
    dis[N]=0;
    Q.push(nod(N,0));//��ʼ̬,NΪ������
    while(!Q.empty()){
        nod temp = Q.top();
        int pos = temp.pos;
        int d = temp.d;
        Q.pop();
        if(d > dis[pos]) continue;
        //�����ڽӱ�������ڵ����̾���
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
