/* *********************************************************** 
//����ͼƥ�䣨�������㷨��DFSʵ�֣�(�ڽӾ�����ʽ) 
//��ʼ����g[][]���߶���Ļ������ 
//����g[i][j]��ʾi->j������߾Ϳ����ˣ���������ұߵ�ƥ�� 
//gû�б��������ʼ��Ϊ0 
//uN��ƥ����ߵĶ�������vN��ƥ���ұߵĶ����� 
//���ã�res=hungary();������ƥ���� 
//�ŵ㣺�����ڳ���ͼ��DFS������·��ʵ�ּ��������� 
//ʱ�临�Ӷ�:O(VE) 
//*************************************************************/ 
//�����Ŵ�0��ʼ�� 
const int MAXN=510;
vector<int> uN,vN;//u,v����Ŀ��ʹ��ǰ����븳ֵ 
int g[MAXN][MAXN];//�ڽӾ��� 
int linker[MAXN];
bool used[MAXN];
bool dfs(int u)
{
	for(int v=0;v<vN.size();v++)
		if(g[u][vN[v]]&&!used[vN[v]])
		{
			used[vN[v]]=true;
			if(linker[vN[v]]==-1||dfs(linker[vN[v]]))
			{
				linker[vN[v]]=u;
				return true;
			}
		}
	return false;
}
int hungary()
{
	int res=0; 
	memset(linker,-1,sizeof(linker));
	for(int u=0;u<uN.size();u++)
	{
		memset(used,false,sizeof(used));
		if(dfs(uN[u]))res++;
	}
	return res;
}
