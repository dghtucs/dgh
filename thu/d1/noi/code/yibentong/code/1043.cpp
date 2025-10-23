#include <iostream>
using namespace std;

int main() {
    int x, y;
    cin >> x >> y;  // 输入两个整数x和y
    
    if (x > y) {
        cout << ">" << endl;  // x大于y
    } else if (x == y) {
        cout << "=" << endl;  // x等于y
    } else {
        cout << "<" << endl;  // x小于y
    }

    return 0;
}
