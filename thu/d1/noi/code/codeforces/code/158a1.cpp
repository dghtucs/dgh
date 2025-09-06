#include <bits/stdc++.h>
using namespace std;




 
int main() {
    int n,k;
    cin >> n >> k;
    int c,temp = 0;
    for(int i = 0;i < n;i++)
    {
        cin >> c;
        if(!c)
        {
            cout << i;
            return 0;
        }
        if(k == (i+1))
        {
            temp = c;
        }
        if(c < temp)
        {
            cout << i;
            return 0;
        }
    }
    cout << n;
}