#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 5;
const int inf = 0x3f3f3f3f;
int N,M,mark[maxn],Max[maxn<<2];

//���µ�ǰ�ڵ�
void pushup(int rt){
    Max[rt] = max(Max[rt<<1],Max[rt<<1|1]);
}

//l:��ǰ�ڵ����˵� r����ǰ�ڵ���Ҷ˵� rt:��ǰ�ڵ�ı��
void build(int l,int r,int rt){
    if(l == r){Max[rt] = mark[l];return;}
    int m = (l+r) >> 1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    pushup(rt);
}

//l:��ǰ�ڵ����˵� r����ǰ�ڵ���Ҷ˵� rt:��ǰ�ڵ�ı�� [L,R]��ѯ������
int query(int L,int R,int l,int r,int rt){
    if(L <= l && R >= r) return Max[rt];
    int m = (l+r) >> 1;
    int res = 0;
    if(L <= m) res = max(res,query(L,R,l,m,rt<<1));
    if(R > m) res = max(res,query(L,R,m+1,r,rt<<1|1));
    return res;
}

//l:��ǰ�ڵ����˵� r����ǰ�ڵ���Ҷ˵� rt:��ǰ�ڵ�ı�� ��L��ֵ��ΪV
void update(int L,int V,int l,int r,int rt){
    if(l==r){Max[rt]=V;return;};
    int m = (l+r) >> 1;
    if(L <= m) update(L,V,l,m,rt<<1);
    else update(L,V,m+1,r,rt<<1|1);
    pushup(rt);
}


int main()
{
    while(scanf("%d%d",&N,&M) != EOF){
        for(int i = 1; i <= N; ++i)
            scanf("%d",&mark[i]);
        build(1,N,1);
        char c;
        int a,b;
        while(M--){
            scanf(" %c%d%d",&c,&a,&b);
            if(c=='Q') printf("%d\n",query(a,b,1,N,1));
            else update(a,b,1,N,1);
        }
    }
    return 0;
}
