/*
 *�㷨���룺
 *����һ������N�����M���ߵ�����ͼ,������С�������ĸ���t(G);
 *
 *�㷨˼�룺
 *�׿�����С�������Ʋ���,���ֻҪ����������������ĸ���,�ǿ�������Matrix-Tree��������;
 *Matrix-Tree����˶�������ͼ��Kirchhoff����,������O(N3)ʱ��������������ĸ���;
 *
 *kruskal�㷨��
 *��ͼG={V,E}�е����б߰��ճ�����С�����������,�ȳ��ı߿��԰�������˳��;
 *��ʼ��ͼG��Ϊ{V,?},��ǰ���ɨ�������ı�,���ɨ�赽�ı�e��G���������������������ͨ��,��������G����;
 *���õ���ͼG������ͼG����С������;
 *
 *����kruskal��������˳��Եȳ��ı߽�������,��Ӧ�ý����г���ΪL0�ıߵĴ�����һ���׶������忴��;
 *��kruskal��������һ���׶κ�õ���ͼΪG0,������ղ�ͬ��˳��Եȳ��ı߽�������,�õ���G0Ҳ�ǲ�ͬ;
 *��ȻG0����������ʽ�Ĳ�ͬ����ͬ,�����ǵ���ͨ�Զ���һ����,����F0����ͨ����ͬ(F0��ʾ�������г���ΪL0�ıߺ��γɵ�ͼ);
 *
 *��kruskal�㷨�е�����ʱ��,������Ҫ��עG���ľ�����̬,��ֻҪ��ע���������ͨ�����(һ�����ò��鼯��ʾ);
 *����ֻҪ��ɨ��������һ�׶κ�����ͨ�Ժ�F0��ͬ,����ͨ����С���۵�����һ״̬��,����ȥ�����ҵ���С������;
 *
 *��������ķ���,���Կ�����һ���׶κͺ���Ĺ�������ȫ������;
 *��һ�׶���Ҫ��ɵ�������ʹG0����ͨ�Ժ�F0һ��,��ֻ��ʹ����С�Ĵ���;
 *�������һ�׶εķ�����,�ٳ�����ɺ�������ķ�����,�������մ�;
 *
 *�����ڵ�һ���׶���,ѡ���ı�����һ����,���бߵĳ��ֶ�ΪL0;
 *�������۵�һ���׶���ν��д��۶���һ����,��ôֻ��Ҫ���㷽����������;
 *��ʱMatrix-Tree����Ϳ��������ó���,ֻ���F0�е�ÿһ����ͨ������������������˼���;
 *
 *Matrix-Tree����:
 *G�����в�ͬ���������ĸ���������Kirchhoff����C[G]�κ�һ��n-1������ʽ������ʽ�ľ���ֵ��
 *n-1������ʽ���Ƕ���r(1��r��n),��C[G]�ĵ�r��,��r��ͬʱȥ����õ����¾���,��Cr[G]��ʾ;
 *
 *�㷨������
 *HDU4408(Minimum Spanning Tree)
 *
 *��Ŀ��ַ��
 *http://acm.hdu.edu.cn/showproblem.php?pid=4408
 *
 *��Ŀ���⣺
 *����һ������N�����M���ߵ�����ͼ,������С�������ĸ���,���ý����pȡģ;
**/

#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
const int N=111;
const int M=1111;
typedef long long LL;
struct Edges
{
    int a,b,c;
    bool operator<(const Edges &x)const
    {
        return c<x.c;
    }
} edge[M];
int n,m;
int mod;
LL f[N],U[N],vist[N];//f,U���ǲ��鼯��U��ÿ�����ʱʹ��
LL G[N][N],C[N][N];//G����֮��Ĺ�ϵ��CΪ�����������õ�Kirchhoff����
vector<int>V[N];//��¼ÿ����ͨ����
int Find(int x,LL f[])
{
    if(x==f[x])
        return x;
    else
        return Find(f[x],f);
}
LL det(LL a[][N],int n)//����������:Matrix-Tree����
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            a[i][j]%=mod;
    int ret=1;
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
            while(a[j][i])
            {
                int t=a[i][i]/a[j][i];
                for(int k=i; k<n; k++)
                    a[i][k]=(a[i][k]-a[j][k]*t)%mod;
                for(int k=i; k<n; k++)
                    swap(a[i][k],a[j][k]);
                ret=-ret;
            }
        if(a[i][i]==0)
            return 0;
        ret=ret*a[i][i]%mod;
    }
    return (ret+mod)%mod;
}
void Solve()
{
    sort(edge,edge+m);//��Ȩֵ����
    for(int i=1;i<=n;i++)//��ʼ�����鼯
    {
        f[i]=i;
        vist[i]=0;
    }
    LL Edge=-1;//��¼��ͬ��Ȩֵ�ı�
    LL ans=1;
    for(int k=0;k<=m;k++)
    {
        if(edge[k].c!=Edge||k==m)//һ����ȵı�,��Ȩֵ��ΪEdge�ı߼���
        {
            for(int i=1;i<=n;i++)
            {
                if(vist[i])
                {
                    LL u=Find(i,U);
                    V[u].push_back(i);
                    vist[i]=0;
                }
            }
            for(int i=1;i<=n;i++) //ö��ÿ����ͨ����
            {
                if(V[i].size()>1)
                {
                    for(int a=1;a<=n;a++)
                        for(int b=1;b<=n;b++)
                            C[a][b]=0;
                    int len=V[i].size();
                    for(int a=0;a<len;a++) //����Kirchhoff����C
                        for(int b=a+1;b<len;b++)
                        {
                            int a1=V[i][a];
                            int b1=V[i][b];
                            C[a][b]=(C[b][a]-=G[a1][b1]);
                            C[a][a]+=G[a1][b1];//��ͨ�����Ķ�
                            C[b][b]+=G[a1][b1];
                        }
                    LL ret=(LL)det(C,len);
                    ans=(ans*ret)%mod;//��V�е�ÿһ����ͨ�������������������
                    for(int a=0; a<len; a++)
                        f[V[i][a]]=i;
                }
            }
            for(int i=1;i<=n;i++)
            {
                U[i]=f[i]=Find(i,f);
                V[i].clear();
            }
            if(k==m)
                break;
            Edge=edge[k].c;
        }
        int a=edge[k].a;
        int b=edge[k].b;
        int a1=Find(a,f);
        int b1=Find(b,f);
        if(a1==b1)
            continue;
        vist[a1]=vist[b1]=1;
        U[Find(a1,U)]=Find(b1,U);//���鼯����
        G[a1][b1]++;
        G[b1][a1]++;
    }
    int flag=0;
    for(int i=2;i<=n&&!flag;i++)
        if(U[i]!=U[i-1])
            flag=1;
    if(m==0)
        flag=1;
    printf("%lld\n",flag?0:ans%mod);
}
int main()
{
    //freopen("C:\\Users\\Administrator\\Desktop\\kd.txt","r",stdin);
    while(~scanf("%d%d%d",&n,&m,&mod))
    {
        memset(G,0,sizeof(G));
        for(int i=1; i<=n; i++)
            V[i].clear();
        for(int i=0; i<m; i++)
            scanf("%d%d%d",&edge[i].a,&edge[i].b,&edge[i].c);
        Solve();
    }
    return 0;
}
