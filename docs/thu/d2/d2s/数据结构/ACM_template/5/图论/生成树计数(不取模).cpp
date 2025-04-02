/*
 *�㷨���룺
 *����һ������ͼG�������������ĸ���t(G);
 *
 *�㷨˼�룺
 *(1)G�Ķ�������D[G]��һ��n*n�ľ���,��������:��i��jʱ,dij=0;��i=jʱ,dij����vi�Ķ���;
 *(2)G���ڽӾ���A[G]��һ��n*n�ľ���,��������:���vi,vj֮���б�ֱ������,��aij=1,����Ϊ0;
 *����ͼG��Kirchhoff����C[G]ΪC[G]=D[G]-A[G];
 *Matrix-Tree����:G�����в�ͬ���������ĸ���������Kirchhoff����C[G]�κ�һ��n-1������ʽ������ʽ�ľ���ֵ��
 *��νn-1������ʽ,���Ƕ���r(1��r��n),��C[G]�ĵ�r��,��r��ͬʱȥ����õ����¾���,��Cr[G]��ʾ;
 *
 *Kirchhoff������������ʣ�
 *(1)�����κ�һ��ͼG,����Kirchhoff����C������ʽ����0,������ΪCÿ��ÿ������Ԫ�صĺ;�Ϊ0;
 *(2)���G�ǲ���ͨ��,������Kirchhoff����C����һ������ʽ������ʽ��Ϊ0;
 *(3)���G��һ����,��ô����Kirchhoff����C����һ��n-1������ʽ������ʽ��Ϊ1;
 *
 *�㷨������
 *SPOJ104(Highways)
 *
 *��Ŀ��ַ��
 *http://www.spoj.com/problems/HIGH/
 *
 *��Ŀ���⣺
 *һ����n�����е���ɹ���,����1��n���,����һЩ����֮������޽����ٹ�·;
 *��Ҫ��ѡ����޽�һЩ���ٹ�·,�Ӷ����һ����ͨ����;
 *�����ж����ַ���,ʹ��������������֮��ǡ��ֻ��һ��·��;
**/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int N=15;

typedef long long LL;

int degree[N];
LL C[N][N];

LL det(LL a[][N],int n)//����������:Matrix-Tree����(����ʽ�ļ���)
{
    LL ret=1;
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
            while(a[j][i])
            {
                LL t=a[i][i]/a[j][i];
                for(int k=i;k<n;k++)
                    a[i][k]=(a[i][k]-a[j][k]*t);
                for(int k=i;k<n;k++)
                    swap(a[i][k],a[j][k]);
                ret=-ret;
            }
        if(a[i][i]==0)
            return 0;
        ret=ret*a[i][i];
    }
    if(ret<0)
        ret=-ret;
    return ret;
}

int main()
{
    int tcase;
    scanf("%d",&tcase);
    while(tcase--)
    {
        memset(degree,0,sizeof(degree));
        memset(C,0,sizeof(C));
        int n,m;
        scanf("%d%d",&n,&m);
        int u,v;
        while(m--)
        {
            scanf("%d%d",&u,&v);
            u--;
            v--;
            C[u][v]=C[v][u]=-1;
            degree[u]++;
            degree[v]++;
        }
        for(int i=0; i<n; ++i)
            C[i][i]=degree[i];
        printf("%lld\n",det(C,n));
    }
    return 0;
}

