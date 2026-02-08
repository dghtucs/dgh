#include <bits/stdc++.h>
typedef long long ll;
const int maxn = 2e5 + 50;
const int mod = 1e9+7;
using namespace std;

ll mu[maxn],not_prime[maxn],prime[maxn];

//��ȡ������Ī����˹����
void getprime(){
    mu[1] = 1;
    not_prime[1] = 1;
    ll cnt = 0;
    for(int i = 2; i <= maxn; ++i){
        if(!not_prime[i]){
            prime[cnt++] = i;
            mu[i]=-1;
            //phi[i]=i-1;
        }
        for(int j = 0; j<cnt && prime[j]*i <= maxn; j++){
            ll x = prime[j]*i;
            not_prime[x] = 1;
            if(i % prime[j] == 0){
                //phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            //else phi[i*prime[j]]=phi[i]*(prime[j]-1);
            mu[x] = -mu[i];
        }
    }
}

//������
ll qpow(ll x,ll y){
    ll res = 1;
    while(y){
        if(y&1) res = res * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return res;
}

int main()
{

}
