#include <bits/stdc++.h>
using namespace std;
//dΪ���ݣ�mx[i][j]��ʾ[i,i+2^j]���������ֵ
int mx[100][100],d[100] = {0},n;
//��ѯ[l,r]�����ֵ
int askmx(int l,int r) {
    int k = log2(r-l+1);
    return max(mx[l][k],mx[r-(1<<k)+1][k]);
}
void init(){
    for(int i = 0; i <= n; ++i) mx[i][0] = d[i];
    for(int j = 1; (1<<j) <= n+1; ++j)
        for(int i = 0; i + (1<<j) <= n+1; ++i)
            mx[i][j] = max(mx[i][j-1],mx[i+(1 << (j-1))][j-1]);
}
int main()
{
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> d[i];
    init();
    int l,r;
    while(cin >> l >> r){
        cout << askmx(l,r) << endl;
    }
}
