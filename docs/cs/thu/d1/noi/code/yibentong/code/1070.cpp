#include <iostream>
#include<iomanip>
using namespace std;

int main() {
    int x, y;
    cin >> x >> y;  // 输入两个整数x和y
    double xd = 1.0*x;

    while(y--)
    {
        xd = xd* 1.001;
    }
    cout << fixed << setprecision(4) << xd;

    return 0;
}
