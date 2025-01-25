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


## 2025年1月20日

### 一本通


[求一个小数的某一位](http://ybt.ssoier.cn:8088/problem_show.php?pid=1082)

```c
#include <iostream>
using namespace std;

int main() {
    int a, b, n;
    cin >> a >> b >> n;

    // Find the n-th digit after the decimal point
    a = a % b; // Start with the remainder after dividing a by b
    for (int i = 1; i < n; ++i) {
        a *= 10;      // Shift the remainder to the left
        a %= b;       // Update the remainder after division
    }
    a *= 10;          // Shift to get the next digit
    cout << (a / b) << endl; // Output the n-th digit

    return 0;
}

```

这个办法是长除法







## 2025年1月21日

### 一本通

快速幂

```c
#include <iostream>
#include <string>
using namespace std;

// 快速幂取模函数
int fastPowerMod(int base, int exp, int mod) {
    int result = 1;  // 初始结果
    base = base % mod;  // 防止 base 一开始就超过 mod
    while (exp > 0) {
        if (exp % 2 == 1) {  // 如果指数是奇数
            result = (result * base) % mod;
        }
        base = (base * base) % mod;  // base 平方
        exp /= 2;  // 指数减半
    }
    return result;
}

int main() {
    int a, b;
    cin >> a >> b;

    // 星期名称数组
    string week[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    // 计算 a^b mod 7
    int offset = fastPowerMod(a, b, 7);

    // 输出对应星期
    cout << week[offset] << endl;

    return 0;
}

```

辗转相除法

```c
#include <iostream>
using namespace std;

// 辗转相除法求最大公约数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;  // 计算余数
        a = b;  // 更新 a 为 b
        b = temp;  // 更新 b 为余数
    }
    return a;  // 返回最大公约数
}

int main() {
    int m, n;
    cin >> m >> n;  // 输入两个正整数

    cout << gcd(m, n) << endl;  // 输出最大公约数

    return 0;
}

```

## 2025年1月22日

### 一本通

筛法求质数

```c
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // Create a boolean array and initialize all elements to true
    vector<bool> isPrime(n + 1, true);
    
    // 0 and 1 are not prime numbers
    isPrime[0] = isPrime[1] = false;
    
    // Sieve of Eratosthenes
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            // Mark all multiples of i as non-prime
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    // Output all prime numbers
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            cout << i << endl;
        }
    }

    return 0;
}

```

#### 开关灯

[开关灯](http://ybt.ssoier.cn:8088/problem_show.php?pid=1109)

```c
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    // Initializing all lights to "True" (on state)
    vector<bool> lights(N, true);

    // Process the toggling operations
    for (int person = 1; person <= M; person++) {
        for (int i = person - 1; i < N; i += person) {
            lights[i] = !lights[i];  // Toggle the light
        }
    }

    // Collect and output the indices of the lights that are off
    vector<int> off_lights;
    for (int i = 0; i < N; i++) {
        if (!lights[i]) {
            off_lights.push_back(i + 1);  // Store the 1-based index
        }
    }

    // Output the result
    stringstream result;
    for (size_t i = 0; i < off_lights.size(); i++) {
        if (i > 0) result << ",";
        result << off_lights[i];
    }
    cout << result.str() << endl;

    return 0;
}


```

#### 绝对差
```c
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int M;
    cin >> M;  // Read the number of integers
    vector<int> numbers(M);  // Create a vector to store the numbers
    
    // Read the sequence of numbers
    for (int i = 0; i < M; i++) {
        cin >> numbers[i];
    }

    // Find the maximum and minimum values
    int max_value = *max_element(numbers.begin(), numbers.end());
    int min_value = *min_element(numbers.begin(), numbers.end());

    // Output the difference between the maximum and minimum values
    cout << max_value - min_value << endl;

    return 0;
}

```

#### 蛇形填数

```c
#include<bits/stdc++.h>
using namespace std;
int a[101][101];
int main()
{
	int n;
	cin>>n;
	int i=0;
	int j=n-1;
	int sum=1;
	int k=0;
	int g=0;
	while(sum<=n*n)
	{
		if(k==0){
			while(i<=n-1-g)
			{
				a[i++][j]=sum;
				sum++;
			}
			i--;
			j--;
		}
		else if(k==1){
			while(j>=g){
				a[i][j--]=sum++;
			}
			j++;
			i--;
		}
		else if(k==2)
		{
			while(i>=g){
				a[i--][j]=sum++;
			}
			i++;
			j++;
		}
		else{
			while(j<=n-g-2){
				a[i][j++]=sum++;
			}
			j--;
			i++;
		}
		k++;
		if(k>4){
			k=0;
			g++;
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

## 2025年1月24日

### 一本通

原来马赛克是这么弄得
中间各像素点新灰度值为该像素点及其上下左右相邻四个像素点原灰度值的平均(舍入到最接近的整数)。


#### 字符串排序

[chuan](http://ybt.ssoier.cn:8088/problem_show.php?pid=2048)

```c
#include <iostream>
#include <vector>
#include <algorithm>  // 包含sort函数
using namespace std;

int main() {
    int n;
    cin >> n;  // 读取国家数量
    vector<string> countries(n);  // 用vector存储国家名称

    // 读取每个国家的名称
    for (int i = 0; i < n; ++i) {
        cin >> countries[i];
    }

    // 对国家名称按字母顺序排序
    sort(countries.begin(), countries.end());

    // 输出排序后的结果
    for (const string& country : countries) {
        cout << country << endl;
    }

    return 0;
}

```
#### 循环字串包含的问题

[t](http://ybt.ssoier.cn:8088/problem_show.php?pid=2050)

本来ai给出的答案是将第一个字符串复制一遍头尾相接，然后判断这个长的字符串是不是后面串的母串，但是评测的时候发现有错误


最后证明还是老老实实循环
```c
#include<iostream>
using std::cin;
using std::cout;
#include<string>
using std::string;
 
int main()
{
	string s01, s02, s1, s2;
	cin >> s01 >> s02;
 
	//默认第一个为长字符串 
	if (s01.size() > s02.size())
	{
		s1 = s01;
		s2 = s02;
	}
	else
	{
		s1 = s02;
		s2 = s01;
	}
 
	//循环遍历判断，注意对应下标即可
	for (int i = 0; i < s1.size(); ++i)
	{
		if (s1[i] == s2[0])
		{
			int index = 0;
			if (i < s1.size() - 1)index = i + 1;
			for (int j = 1; j < s2.size(); ++j)
			{
				if (s1[index] != s2[j])break;
 
				if (j == s2.size() - 1) 
				{
					cout << "true";
					exit(1);
				}
 
				if (index == s1.size() - 1)index = 0;
				else index++;
			}
		}
 
		if (i == s1.size() - 1)
		{
			cout << "false";
			exit(1);
		}
	}
 
}
```













