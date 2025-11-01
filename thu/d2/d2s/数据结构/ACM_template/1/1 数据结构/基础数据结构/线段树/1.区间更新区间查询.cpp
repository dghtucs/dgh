测试地址
// https://www.luogu.org/problemnew/show/P3372

#include<bits/stdc++.h>
using namespace std;
#define lson (o << 1)
#define rson (o << 1|1)
const int maxn = 1e5+10;
const int INF = 1e9;
typedef long long LL;
struct Tree{
	LL min,max,sum,add;
};
LL a[maxn];
struct Seg_Tree{
	Tree tree[maxn<<2];
	void pushup(int o,int l,int r){
		tree[o].min = min(tree[lson].min,tree[rson].max);
		tree[o].max = max(tree[lson].max,tree[rson].max);
		tree[o].sum = tree[lson].sum + tree[rson].sum;
	}
	void pushdown(int o,int l,int r){
		int m = (l+r)>>1;
		if(tree[o].add){
			tree[lson].add += tree[o].add;
			tree[lson].sum += (m-l+1)*tree[o].add;
			tree[lson].min += tree[o].add;
			tree[lson].max += tree[o].add;
	
			tree[rson].add += tree[o].add;
			tree[rson].sum += (r-m)*tree[o].add;
			tree[rson].min += tree[o].add;
			tree[rson].max += tree[o].add;
			tree[o].add = 0;
		}
	}
	void up(Tree & a,Tree b){
		a.min = min(a.min,b.min);
		a.max = max(a.max,b.max);
		a.sum += b.sum;
	}
	void build(int o,int l,int r,LL *a){
		// cout<<l<<" "<<r<<endl;
		tree[o].add = 0;
		if(l == r)
		 	{
		 		tree[o].min = tree[o].max = tree[o].sum = a[l];
		 		// cout<<l <<" "<<a[l]<<endl;
		 	}
		else{
			int m = (l+r)>>1;
			build(lson,l,m,a);
			build(rson,m+1,r,a);
			pushup(o,l,r);
		}
	}
	void update(int o,int l,int r,int L,int R,int v){
		if(L <= l && R >= r){
			tree[o].add += v;
			tree[o].sum += (r-l+1)*v;
			tree[o].max += v;
			tree[o].min += v;
			return ;
		}
		pushdown(o,l,r);
		int m = (l+r)/2;
		if(L <= m)
			update(lson,l,m,L,R,v);
		if(R > m)
			update(rson,m+1,r,L,R,v);
		pushup(o,l,r);
	}
	Tree query(int o,int l,int r,int L,int R){
		
		if(L <= l && R >= r)
		{
			return tree[o];
		}
		Tree tmp;
		tmp.min = INF,tmp.max = -INF,tmp.sum = 0;
		pushdown(o,l,r);
		int m = (l+r)>>1;
		if(L <= m)
			up(tmp,query(lson,l,m,L,R));
		if(R > m)
			up(tmp,query(rson,m+1,r,L,R));
		// cout<<tmp.sum<<endl;
		return tmp;
	}
}; 
Seg_Tree solver; 
int main(void){

	int N,Q;cin>>N>>Q;
	for(int i =1;i <= N; ++i)
		scanf("%lld",&a[i]);
	solver.build(1,1,N,a);
	// cout<<Query(1,1,N,1,1).sum<<endl;
	while(Q--){
		LL c,x,y,v;
		scanf("%lld%lld%lld",&c,&x,&y);
		if(c == 1){
			scanf("%lld",&v);
			solver.update(1,1,N,x,y,v);
		}
		else{
			printf("%lld\n",solver.query(1,1,N,x,y).sum);
		}
	}


	return 0;
}
