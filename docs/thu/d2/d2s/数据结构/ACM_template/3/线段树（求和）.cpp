#include <bits/stdc++.h>
#define FAST ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
const int maxn = 2e5+300;
const int inf = 0x3f3f3f3f;
using namespace std;

int N,M,a[maxn],Sum[maxn<<2];

//���µ�ǰ�ڵ�
void pushup(int& rt,int l,int r){
    rt = l+r;
}

//l:��ǰ�ڵ����˵� r����ǰ�ڵ���Ҷ˵� rt:��ǰ�ڵ�ı��
void build(int l,int r,int rt){
    if(l == r){
        Sum[rt] = a[l];
        return;
    }
    int m = (l+r) >> 1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    pushup(Sum[rt],Sum[rt<<1],Sum[rt<<1|1]);
}

//l:��ǰ�ڵ����˵� r����ǰ�ڵ���Ҷ˵� rt:��ǰ�ڵ�ı�� [L,R]��ѯ������
int query(int L,int R,int l,int r,int rt){
    int m = (l+r) >> 1;
    if(L<=l&&R>=r) return Sum[rt];
    if(R <= m) return query(L,R,l,m,rt<<1);
    else if(L >= m+1) return query(L,R,m+1,r,rt<<1|1);
    else{
        int res = 0;
        pushup(res,query(L,R,l,m,rt<<1),query(L,R,m+1,r,rt<<1|1));
        return res;
    }
}

//l:��ǰ�ڵ����˵� r����ǰ�ڵ���Ҷ˵� rt:��ǰ�ڵ�ı�� ��L��ֵ��ΪV
void update(int L,int V,int l,int r,int rt){
    if(l==r){Sum[rt]=V;return;}
    int m = (l+r) >> 1;
    if(L <= m) update(L,V,l,m,rt<<1);
    else update(L,V,m+1,r,rt<<1|1);
    pushup(Sum[rt],Sum[rt<<1],Sum[rt<<1|1]);
}

int main(){
}
