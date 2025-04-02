#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=123456789;
struct matrix{
    ll a[11][11]; //begin with 1
    int r,c;
    matrix(int n,int m):r(n),c(m){memset(a,0,sizeof(a));}
    ll* operator[](int x){return a[x];}
    friend matrix operator*(matrix A,matrix B)
    {
        matrix C(A.r,B.c);
        for(int i=1;i<=A.r;i++)
            for(int j=1;j<=B.c;j++)
                for(int k=1;k<=A.c;k++){
                    C[i][j]+=(A[i][k]*B[k][j])%mod;
                    C[i][j]+=mod;
                    C[i][j]%=mod;
                }
        return C;
    }
};

matrix qpow(matrix A,ll m)//方阵A的m次幂
{
    matrix ans(A.r,A.c);
    for(int i=1;i<=A.r;i++) ans.a[i][i]=1; //单位矩阵
    while(m)
    {
        if(m&1)ans=ans*A;
        A=A*A;
        m>>=1;
    }
    return ans;
}

int main()
{
    ll T,n;
    for(cin>>T;T--;)
    {
        scanf("%lld",&n);
        matrix A(6,6);
        A[1][1]=1;
        A[1][2]=2;
        A[1][3]=1;
        A[1][4]=3;
        A[1][5]=3;
        A[1][6]=1;
        A[2][1]=1;
        A[3][3]=1;
        A[4][3]=1;
        A[4][4]=1;
        A[5][3]=1;
        A[5][4]=2;
        A[5][5]=1;
        A[6][3]=1;
        A[6][4]=3;
        A[6][5]=3;
        A[6][6]=1;
        matrix X2(6,1);
        X2[1][1]=2;
        X2[2][1]=1;
        X2[3][1]=1;
        X2[4][1]=2;
        X2[5][1]=4;
        X2[6][1]=8;
        matrix Xn=qpow(A,n-2)*X2;
        printf("%lld\n",Xn[1][1]);
    }
}·
