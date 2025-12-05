#include <bits/stdc++.h>
typedef long long ll;
const int maxn = 2e5+300;
const int inf = 0x3f3f3f3f;
using namespace std;
int a[maxn],Sum[maxn<<2],pos[maxn],lazy[maxn<<2];

void pushup(int rt){
    Sum[rt] = Sum[rt<<1] + Sum[rt<<1|1];
}

void pushdown(int l,int r,int rt){
    //�����ֵ
    if(lazy[rt]){
        int m = (l+r) >> 1;
        lazy[rt<<1] = lazy[rt];
        lazy[rt<<1|1] = lazy[rt];
        Sum[rt<<1] = lazy[rt] * (m-l+1);
        Sum[rt<<1|1] = lazy[rt] * (r-m);
        lazy[rt] = 0;
    }
    //��������
    /*if(lazy[rt]){
        int m = (l+r) >> 1;
        lazy[rt<<1] += lazy[rt];
        lazy[rt<<1|1] += lazy[rt];
        Sum[rt<<1] += lazy[rt] * (m-l+1);
        Sum[rt<<1|1] += lazy[rt] * (r-m);
        lazy[rt] = 0;
    }*/
}
//l:��ǰ�ڵ����˵� r����ǰ�ڵ���Ҷ˵� rt:��ǰ�ڵ�ı��
void build(int l,int r,int rt){
    if(l == r){
        pos[l] = rt;
        Sum[rt] = a[l];
        return;
    }
    int m = (l+r) >> 1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    pushup(rt);
}
//l:��ǰ�ڵ����˵� r����ǰ�ڵ���Ҷ˵� rt:��ǰ�ڵ�ı�� [L,R]��ѯ������
int query(int L,int R,int l,int r,int rt){
    if(L <= l && R >= r) return Sum[rt];
    int m = (l+r) >> 1;
    int res = 0;
    pushdown(l,r,rt);
    if(L <= m) res += query(L,R,l,m,rt<<1);
    if(R > m) res += query(L,R,m+1,r,rt<<1|1);
    return res;
}
//l:��ǰ�ڵ����˵� r����ǰ�ڵ���Ҷ˵� rt:��ǰ�ڵ�ı�� ��L��ֵ��ΪV
void update(int L,int V,int l,int r,int rt){
    if(l==r){Sum[rt]=V;return;}
    int m = (l+r) >> 1;
    pushdown(l,r,rt);
    if(L <= m) update(L,V,l,m,rt<<1);
    else update(L,V,m+1,r,rt<<1|1);
    pushup(rt);
}
void segupdate(int L,int R,int l,int r,int rt,int lzy){
    if(L <= l && R >= r){
        //�����ֵ
        lazy[rt]=lzy;
        Sum[rt] = (r-l+1) * lzy;
        //����Ӽ�
        /*lazy[rt]+=lzy;
        sum[rt]+=(r-l+1) * lzy;*/
        return;
    }
    int m = (l+r) >> 1;
    pushdown(l,r,rt);
    if(L <= m) segupdate(L,R,l,m,rt<<1,lzy);
    if(R > m) segupdate(L,R,m+1,r,rt<<1|1,lzy);
    pushup(rt);
    return;
}
