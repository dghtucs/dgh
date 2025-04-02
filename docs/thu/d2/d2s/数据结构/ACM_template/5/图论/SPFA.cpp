/* 
 * ��Դ���·SPFA 
 * ʱ�临�Ӷ� 0(kE) 
 * ����Ƕ���ʵ�֣���ʱ��ĳ�ջʵ�ֻ���ӿ죬�������޸� 
 * ������Ӷ��ǲ����� 
 */ 
const int MAXN=1010;
const int INF=0x3f3f3f3f;
struct Edge
{
	int v;
	int cost;
	Edge(int _v=0,int _cost=0):v(_v),cost(_cost){}
};
vector<Edge>E[MAXN];
void addedge(int u,int v,int w)
{
	E[u].push_back(Edge(v,w));
}
bool vis[MAXN];//�ڶ��б�־ 
int cnt[MAXN];//ÿ���������д��� 
int dist[MAXN];
bool SPFA(int start,int n)
{
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;i++)dist[i]=INF;
	vis[start]=true;
	dist[start]=0;
	queue<int>que;
	while(!que.empty())que.pop();
	que.push(start);
	memset(cnt,0,sizeof(cnt));
	cnt[start]=1;
	while(!que.empty())
	{
		int u=que.front();
		que.pop();
		vis[u]=false;
		for(int i=0;i<E[u].size();i++)
		{
			int v=E[u][i].v;
			if(dist[v]>dist[u]+E[u][i].cost)
			{
				dist[v]=dist[u]+E[u][i].cost;
				if(!vis[v])
				{
					vis[v]=true;
					que.push(v);
					if(++cnt[v]>n)return false;
					//cnt[i]Ϊ����д����������ж��Ƿ���ڸ�����· 
				}
			}
		}
	}
	return true;
}
