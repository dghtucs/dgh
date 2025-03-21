#include <iostream>
using namespace std;
int a[10];
int main() {
    for(int i = 0;i < 5;i++)
        cin >> a[i];
    for(int i = 0;i <5;i++)
    {
        int three = a[i] / 3;
        a[i] = three;
        a[(i+1)%5] += three;
        a[(i-1+5)%5] += three;

    }
    for(int i = 0;i < 5;i++)
    {
        printf("%5d",a[i]);
    }
    return 0;
}
