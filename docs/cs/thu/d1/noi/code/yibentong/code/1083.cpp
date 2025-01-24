#include <iostream>
#include <string>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;

    // 星期名称数组
    string week[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    // 计算偏移量并输出结果
    long long offset = pow(a , b) % 7;  // 计算偏移
    cout << week[offset] << endl;

    return 0;
}
