/* 
 * Kruskal�㷨��MST 
 */ 
namespace MST
{
	const int MAXN=1e5+5;//������ 
	const int MAXM=1e5+5;//������ 
	int F[MAXN];//���鼯ʹ�� 
	struct Edge
	{
		int u,v,w;
	}edge[MAXM];//�洢�ߵ���Ϣ���������/�յ�/Ȩֵ 
	int tol;//�������ӱ�ǰ��ֵΪ0 
	void init()//��ʼ�� 
	{
		tol=0;
		memset(F,-1,sizeof(F));
		memset(edge,0,sizeof(edge));
	}
	void addedge(int u,int v,int w)
	{
		edge[tol].u=u;
		edge[tol].v=v;
		edge[tol++].w=w;
	}
	bool cmp(Edge a,Edge b)//�����������߰���Ȩֵ��С�������� 
	{
		return a.w<b.w;
	}
	int find(int x)//���鼯ʹ�� 
	{
		if(F[x]==-1)return x;
		else return F[x]=find(F[x]);
	}
	int Kruskal(int n)//���������������С��������Ȩֵ���������ͨ����-1 
	{
		sort(edge,edge+tol,cmp);
		int cnt=0;//�������ı��� 
		int ans=0;
		for(int i=0;i<tol;i++)
		{
			int u=edge[i].u;
			int v=edge[i].v;
			int w=edge[i].w;
			int t1=find(u);
			int t2=find(v);
			if(t1!=t2)
			{
				ans+=w;
				F[t1]=t2;
				cnt++;
			}
			if(cnt==n-1)break;
		}
		if(cnt<n-1)return -1;//����ͨ
		else return ans;
	}
}
