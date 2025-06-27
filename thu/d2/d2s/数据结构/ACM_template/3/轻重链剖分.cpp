/*
 * @Description: 
 * @Version: 
 * @Author: LotusIR
 * @Date: 2019-11-29 08:33:38
 * @LastEditors  : LotusIR
 * @LastEditTime : 2020-01-07 23:14:55
 */
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 1e5+200;
int n,weight[maxn],Size[maxn],sum[maxn];//nΪ������weightΪ��Ȩ��SizeΪ������С��sumΪǰ׺������
int dep[maxn],cnt;//depΪ��ȣ�cntΪdfs���õı��
vector<int> E[maxn];//�ڽӱ�
int parent[maxn],son[maxn],top[maxn],rk[maxn];//���ڵ㡢�ض��ӡ��������ˡ����dfs����

//�������ʷ֣�����Ȩ��������߶�����̬��ѯ����������룬����LCA
//��дdfs1���ɸ�дΪ�����ʷ�
void dfs1(int u,int fa,int root){
    parent[u]=fa;dep[u]=dep[fa]+1;Size[u]=1;
    for(int v,i = 0; i < E[u].size(); ++i){
        if((v=E[u][i])!=fa){
            dfs1(v,u,root);Size[u]+=Size[v];
            if(Size[v]>Size[son[u]]) son[u]=v;
        }
    }

}

int dfs2(int u,int t){
    top[u] = t;
    rk[u] = ++cnt;
    sum[rk[u]] = weight[u];
    if(son[u]!=0) dfs2(son[u],t);
    for(int v,i = 0; i < E[u].size(); ++i)
        if((v=E[u][i])!=son[u]&&v!=parent[u]) dfs2(v,v);
}

//��ѯ����a��b·���ĵ�Ȩ��
int Treequery(int a,int b){
    int res = 0;
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]]) swap(a,b);
        res += sum[rk[a]]-sum[rk[top[a]]-1];
        a = parent[top[a]];
    }
    if(dep[a]<dep[b]) swap(a,b);
    res += sum[rk[a]]-sum[rk[b]-1];
    return res;
}

int pre_sum(){
    for(int i = 1; i <= n; ++i) sum[i]+=sum[i-1];
}
