#include <bits/stdc++.h>
typedef long long ll;
const int maxn = 1e5 + 200;
using namespace std;

//acnt为逆序对的数量
int a[maxn],b[maxn],acnt,pay,i,j,cnt;

void Merge(int l,int m,int r){
    cnt = l,i=l,j=m+1;
    while(i  <= m && j <= r){
        if(a[i] <= a[j])
            b[cnt++] = a[i++];
        else{
            b[cnt++] = a[j++];
            //统计逆序对
            acnt += m-i+1;
        }
    }
    while(i <= m) b[cnt++] = a[i++];
    while(j <= r) b[cnt++] = a[j++];
    for(int i = l; i <= r; i++) a[i]=b[i];
}

void Mergesort(int l,int r){
    if(l < r - 1){
        Mergesort(l,(l+r)>>1);
        Mergesort(((l+r)>>1)+1,r);
    }
    Merge(l,(l+r)>>1,r);
    return;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    while(cin >> n){
        acnt = 0;
        for(int i = 1; i <= n;++i) cin >> a[i];
        Mergesort(1,n);
        for(int i = 1; i <= n;++i) cout << a[i] << " ";
        cout << endl;
    }
}
