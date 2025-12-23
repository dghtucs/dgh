#include <bits/stdc++.h>
const int maxn = 200;
using namespace std;
struct edge{
    int from;
    int to;
    int val;
    edge(int a = 0,int b = 0,int c = 0){from=a;to=b;val=c;}
    friend bool operator > (edge a,edge b){
        return a.val > b.val;
    }
};
int N,M,father[maxn];
priority_queue< edge,vector<edge>,greater<edge> > Q;
int Find(int a){ return father[a]==a?a:father[a]=Find(father[a]); }
void Union(int a,int b){ father[Find(b)] = Find(a); }
void init(){
    for(int i = 1; i <= M; ++i) father[i]=i;
    while(!Q.empty()) Q.pop();
}

void kruscal(){
    int ans = 0,cnt = 0;
    while(!Q.empty() && cnt != M-1){
        edge temp = Q.top();
        Q.pop();
        int f = temp.from,t = temp.to,v = temp.val;
        if(Find(t)!=Find(f)){
            Union(f,t);
            cnt++;
            ans+=v;
        }
    }
    if(cnt != M-1) puts("?");
    else printf("%d\n",ans);
}


int main()
{
    while(scanf("%d",&N)){
        if(N==0) break;
        scanf("%d",&M);
        init();
        for(int i = 0; i < N; i++){
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            Q.push(edge(a,b,c));
        }
        if(N<M-1){puts("?");continue;}
        kruscal();
    }
    return 0;
}
