/*
����� = ��ͼG������������
������>���������� = ��ͼG'�����
*/
//�����ģ��
#include<bits/stdc++.h>
const int MAXN=102;
int mx;//�������(Ҫ��ʼ��Ϊ0)
int x[MAXN],tuan[MAXN];
int can[MAXN][MAXN];//can[i]��ʾ���Ѿ�ȷ���˾�ѡ����i���������������ڵ�ǰ���»��п��ܱ��ӽ�����ŵĽ�㼯��
int num[MAXN];//num[i]��ʾ�ɽ��i�����n���ɵ�����ŵĽ����
bool g[MAXN][MAXN];//�ڽӾ���(��1��ʼ)
int n,m;
bool dfs(int tot,int cnt)
{
	int i,j,k;
	if(tot==0)
	{
		if(cnt>mx)
		{
			mx=cnt;
			for(i=0;i<mx;i++)
			{
				tuan[i]=x[i];
			}
			return true;
		}
		return false;
	}
	for(i=0;i<tot;i++)
	{
		if(cnt+(tot-i)<=mx)return false;
		if(cnt+num[can[cnt][i]]<= mx)return false;
		k=0;
		x[cnt]=can[cnt][i];
		for(j=i+1;j<tot;j++)
		{
			if(g[can[cnt][i]][can[cnt][j]])
			{
				can[cnt+1][k++]=can[cnt][j];
			}
		}
		if(dfs(k,cnt+1))return false;
	}
	return false;
}
void MaxTuan()
{
	int i,j,k;
	mx=1;
	for(i=n;i>=1;i--)
	{
		k=0;
		x[0]=i;
		for(j=i+1;j<=n;j++)
		{
			if(g[i][j])
			{
				can[1][k++]=j;
			}
		}
		dfs(k,1);
		num[i]=mx;
	}
}
int main()
{
	while(scanf("%d",&n)&&n)
	{
		int i,j;
		memset(g,0,sizeof(g));
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				scanf("%d",&g[i][j]);
			}
		}
		mx=0;
		MaxTuan();
		printf("%d\n",mx);
	}
	return 0;
}
