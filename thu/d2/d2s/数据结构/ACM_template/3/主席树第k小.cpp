/*
 * @Description: 
 * @Version: 
 * @Author: LotusIR
 * @Date: 2019-12-02 15:25:26
 * @LastEditors  : LotusIR
 * @LastEditTime : 2020-01-10 17:15:01
 */
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 1e5+50;

int a[maxn],b[maxn],n,m,T,cnt;
int lson[maxn<<5],rson[maxn<<5],val[maxn<<5],rk,root[maxn];

int idx(int x){
    return lower_bound(b+1,b+1+cnt,x)-b;
}

void build(int &u,int l,int r){
    u=rk++;val[u]=0;
    if(l==r) return;
    int mid = l+r >> 1;
    build(lson[u],l,mid);
    build(rson[u],mid+1,r);
}

void update(int &u,int lst,int l,int r,int V){
    u=rk++;rson[u]=rson[lst];lson[u] = lson[lst];val[u]=val[lst];val[u]++;
    if(l==r) return;
    int mid = l+r >> 1;
    if(V<=mid) update(lson[u],lson[lst],l,mid,V);
    else update(rson[u],rson[lst],mid+1,r,V);
}

int query(int L,int R,int l,int r,int k){
    if(l==r) return l;
    int mid = l+r>>1,x = val[lson[R]]-val[lson[L]];
    if(x>=k) return query(lson[L],lson[R],l,mid,k);
    else return query(rson[L],rson[R],mid+1,r,k-x);
}

int main(){
    int kase = 0;
    while(~scanf("%d",&n)){
        rk = 0;
        for(int i = 1; i <= n; ++i) scanf("%d",&a[i]),b[i]=a[i];
        sort(b+1,b+1+n);
        cnt = unique(b+1,b+1+n)-b-1;
        build(root[0],1,cnt);
        for(int i = 1; i <= n; ++i) update(root[i],root[i-1],1,cnt,idx(a[i]));
        scanf("%d",&m);
        printf("Case %d:\n",++kase);
        while(m--){
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",b[query(root[l-1],root[r],1,cnt,r-l+1-(r-l)/2)]);
        }
    }
}

