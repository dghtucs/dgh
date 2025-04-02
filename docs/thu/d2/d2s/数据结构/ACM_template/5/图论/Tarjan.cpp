/* 
 * Tarjan�㷨 
 * ���Ӷ�O(N+M) 
 */ 
namespace Tarjan
{
	const int MAXN=20010;//����
	const int MAXM=50010;//����
	struct Edge
	{
		int to,nxt;
	}edge[MAXM];
	int head[MAXN],tot;
	int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];//Belong�����ֵ��1~scc
	int Index,top;
	int scc;//ǿ��ͨ�����ĸ���
	bool Instack[MAXN]; 
	int num[MAXN];//����ǿ��ͨ����������ĸ�����������1~scc 
	//num���鲻һ����Ҫ�����ʵ�����
	void addedge(int u,int v)
	{
		edge[tot].to=v;edge[tot].nxt=head[u];head[u]=tot++;
	}
	void Tarjan(int u)
	{
		int v;
		Low[u]=DFN[u]=++Index;
		Stack[top++]=u;
		Instack[u]=true;
		for(int i=head[u];~i;i=edge[i].nxt)
		{
			v=edge[i].to;
			if(!DFN[v])
			{
				Tarjan(v);
				if(Low[u]>Low[v])Low[u]=Low[v];
			}
			else if(Instack[v]&&Low[u]>DFN[v])
				Low[u]=DFN[v];
		}
		if(Low[u]==DFN[u])
		{
			scc++;
			do
			{
				v=Stack[--top];
				Instack[v]=false;
				Belong[v]=scc;
				num[scc]++;
			}
			while(v!=u);
		}
	}
	void solve(int N)
	{
		memset(DFN,0,sizeof(DFN));
		memset(Instack,false,sizeof(Instack));
		memset(num,0,sizeof(num));
		Index=scc=top=0;
		for(int i=1;i<=N;i++)
			if(!DFN[i])
				Tarjan(i);
	}
	void init()
	{
		tot=0;
		memset(head,-1,sizeof(head));
	}
}

