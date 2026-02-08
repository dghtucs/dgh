#include<stdio.h>
#include<string.h>
#include<math.h>
#include<queue>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
const int MAXN=3000+7;
struct point
{
    double x,y,s;
}a[MAXN],b[MAXN];
bool map[MAXN][MAXN];
bool vis[MAXN];
int dx[MAXN],dy[MAXN];/*dx[i]表示左集合i顶点的距离编号，dy[i]表示右集合i顶点的距离编号,还有就是这里就是bfs找增广路用的数组 对于u-->v可达就有dy[v] = dx[u] + 1 */
int cx[MAXN],cy[MAXN];
int dis;
int n,T,m;
bool searchpath()
{
    queue<int>q;
    dis=INF;
    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for(int i=1;i<=n;i++)
    {
        //cx[i]表示左集合i顶点所匹配的右集合的顶点序号
        if(cx[i]==-1)
        {
            //将未遍历的节点 入队 并初始化次节点距离为0
            q.push(i);
            dx[i]=0;
        }
    }
    //广度搜索增广路径
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        if(dx[u]>dis) break;
        //取右侧节点，所以用m。 
        for(int v=1;v<=m;v++)
        {
            //右侧节点的增广路径的距离 
            if(map[u][v]&&dy[v]==-1)
            {
                dy[v]=dx[u]+1;//v对应的距离 为u对应距离加1
                if(cy[v]==-1) dis=dy[v];
                else
                {
                    dx[cy[v]]=dy[v]+1;
                    q.push(cy[v]);
                }
            }
        }
    }
    return dis!=INF;
}
 //寻找路径 深度搜索
int dfs(int u)
{
    for(int v=1;v<=m;v++)
    {
        //如果该点没有被遍历过 并且距离为上一节点+1 
        if(map[u][v]&&!vis[v]&&dy[v]==dx[u]+1)
        {
            //对该点染色，即是进行标记   
            vis[v]=true;
            if(cy[v]!=-1&&dy[v]==dis)
            continue;
            if(cy[v]==-1||dfs(cy[v]))
            {
                cx[u]=v;
                cy[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
 //得到最大匹配的数目   
int MaxMatch() 
{
    memset(cx,-1,sizeof(cx));
    memset(cy,-1,sizeof(cy));
    int res=0;
    while(searchpath())
    {
        memset(vis,false,sizeof(vis));
        for(int i=1;i<=n;i++)
        {
            if(cx[i]==-1)
            res+=dfs(i);
        }           
    }
    return res;
}
int main()
{
    int t,k=1;
    scanf("%d",&t);
    while(t--)
    {
        memset(map,false,sizeof(map));
        scanf("%d",&T);
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        scanf("%lf%lf%lf",&a[i].x,&a[i].y,&a[i].s);
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
        scanf("%lf%lf",&b[i].x,&b[i].y);
        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(a[i].s*T>=sqrt((a[i].x-b[j].x)*(a[i].x-b[j].x)+(a[i].y-b[j].y)*(a[i].y-b[j].y)))
            map[i][j]=true;
        }
        int ans=MaxMatch();  
        printf("Scenario #%d:\n%d\n\n",k++,ans);
    }
}