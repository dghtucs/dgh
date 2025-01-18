在这里解决编程和相关数学的学习

# 2025年1月

## 2025年1月18日



### 一本通

[苹果](http://ybt.ssoier.cn:8088/problem_show.php?pid=1038)

这个题主要是要记住这个方法k=ceil(k);

---

[三个数](http://ybt.ssoier.cn:8088/problem_show.php?pid=2053)

```cpp
#include <iostream>
#include <algorithm>  // 包含 sort 函数
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;  // 输入三个整数
    
    // 将三个数放入数组中
    int arr[] = {a, b, c};
    
    // 对数组进行排序（默认是从小到大排序）
    sort(arr, arr + 3, greater<int>());  // 使用 greater<int>() 实现从大到小排序
    
    // 输出排序后的结果
    cout << arr[0] << " " << arr[1] << " " << arr[2] << endl;
    
    return 0;
}
```
放进数组还可以这么操作
// 将三个数放入数组中
    int arr[] = {a, b, c};
















