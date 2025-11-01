const int INF=0x3f3f3f3f;
const int MAXN=550;
int dist[MAXN];
struct Edge
{
	int u,v;
	int cost;
	Edge(int _u=0,int _v=0,int _cost=0):u(_u),v(_v),cost(_cost){}
};
vector<Edge>E;
bool bellman_ford(int start,int n)//��ı�Ŵ�1��ʼ 
{
	for(int i=1;i<=n;i++)dist[i]=INF;
	dist[start]=0;
	for(int i=1;i<n;i++)//�����n-1��
	{
		bool flag=false;
		for(int j=0;j<E.size();j++)
		{
			int u=E[j].u;
			int v=E[j].v;
			int cost=E[j].cost;
			if(dist[v]>dist[u]+cost)
			{
				dist[v]=dist[u]+cost;
				flag=true;
			}
		}
		if(!flag)return true;//û�и�����·
	}
	for(int j=0;j<E.size();j++)
		if(dist[E[j].v]>dist[E[j].u]+E[j].cost)
			return false;//�и�����· 
	return true;//û�и�����· 
}
