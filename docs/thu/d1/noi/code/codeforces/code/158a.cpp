#include <bits/stdc++.h>
using namespace std;



int a[55];
 
int main() {
    int n,k;
    cin >> n >> k;
    for(int i = 1;i <= n;i++)
    {
        cin >> a[i];
        if(a[i] == 0)
        {
            cout << i-1;
            return 0;
        }
    }
    int count = k;
    for(int i = k+1;i <= n;i++)
    {
        if(a[i] == a[i+1])
            count++;
    }
    cout << count;
    return 0;
}