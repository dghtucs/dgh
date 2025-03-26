


## part1 cpp基础

### 函数

```c
#include <iostream>
using namespace std;

int sum(int x)
{
    int res = 0;
    for(int i = 1;i <= x;i++)
    {
        res += i;
    }
    return res;
    
}

int main()
{
    int n;
    cin >> n;
    int homes = 2;
    while(homes <= n)
    {
        int s1 = sum(homes);
        int myhome = 1;
        while(myhome <= homes)
        {
            if(s1 - 3*myhome == n)
            {
                cout << myhome << " " << homes;
            }
            myhome++;
        }
        homes++;
    }
    

    return 0;
}

```


```c
#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;
long long max(long long a,long long b)
{
    if(a>b)
        return a;
    return b;
}
bool isprime(long long x)
{
    if(x < 2)
    {
        return false;
    }
    ll limit = sqrt(x);
    for(int i = 2;i <= limit;i++)
    {
        if(x % i == 0)
            return false;
    }
    return true;
    
}

int main()
{
    ll n;
    cin >> n;
    long long res = 0;
    for(ll i = 2;i <= n/2 ;i++) // 这里不是n的平方，而是n的一半
    {
        if(isprime(i) && isprime(n-i))
        {
            res = max(res,i*(n-i));
        }
    }
    cout << res;
    
    

    return 0;
}
```

## part2 基础算法



## part3 数据结构





















