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

### codeforces

[求第k位](https://codeforces.com/problemset/problem/158/A)

这个题我想更新一个count和k作比较，但是不知道怎么搞

最快的答案
```c
#include <stdio.h>
#include <stdlib.h>
int main(){
    int n,k;
    scanf("%d %d", &n, &k);
    int curr, ak=0;
    for(int i=0;i<n;i++){
        scanf("%d", &curr);
        if (curr==0){
            printf("%d", i);
            exit(0);
        }
        if (k==(i+1)){
            ak=curr;
        }
        if (curr<ak){
            printf("%d", i);
            exit(0);
        }
    }
    printf("%d", n);
    return 0;
}

```
我本来写的代码是
```cpp
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
```

过不了第三个点



## 2025年1月19日

### 一本通

[买笔](http://ybt.ssoier.cn:8088/problem_show.php?pid=2059)


这个思路太秒了
```c
#include<stdio.h>
using namespace std;
int main()
{
	int a,b,c;
	int x,y;
	scanf("%d",&x);
	c=x/4;
	y=x%4;
	switch(y)
	{
		case 0:
		a=0;
		b=0;
		break;
		case 1:
		a=0;
		b=1;
		c--;
		break;
		case 2:
		a=1;
		b=0;
		c--;
		break;
		case 3:	
		a=1;
		b=1;
		c-=2;
	}
	printf("%d %d %d",a,b,c);
	return 0;
}
```

在 C++ 中，`int` 类型通常占用 4 字节（32 位）。因此，我们可以计算出在 1 MB 的内存中可以存放多少个 `int`。

### 计算过程：
1 MB = 1024 KB  
1 KB = 1024 字节  
因此，1 MB = 1024 * 1024 字节 = 1,048,576 字节。

如果每个 `int` 类型占用 4 字节，那么可以存放的 `int` 数量为：

\[
\text{int 数量} = \frac{1,048,576 \text{ 字节}}{4 \text{ 字节/个}} = 262,144 \text{ 个 int}
\]

### 结论：
1 MB 的内存可以存放 262,144 个 `int`。




