#include <iostream>
using namespace std;
// 定义两个全局数组用于合并排序
long long L[200005], R[200005];
// 结构体 Point，用于表示二维点的坐标
struct Point {
    long long x, y; // x 和 y 坐标
};

// 计算点 c 相对于线段 (0, ay) 到 (bx, 0) 的位置
long long ToLeft(long long ay, long long bx, Point c) {
    // 使用叉积判断点 c 相对于线段的位置
    return (bx - 0) * (c.y - ay) - (c.x - 0) * (0 - ay);
}
void mergeSort(long long arr[], long long left, long long right);
void merge(long long arr[], long long left, long long mid, long long right);
// 合并排序
void mergeSort(long long arr[], long long left, long long right) {
    // 如果左边小于右边，进行分治
    if (left < right) {
        long long mid = left + (right - left) / 2; // 计算中间位置
        // 递归地对左右子数组进行排序
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        // 合并已排序的子数组
        merge(arr, left, mid, right);
    }
}

// 合并两个已排序的子数组
void merge(long long arr[], long long left, long long mid, long long right) {
    long long n1 = mid - left + 1; // 左子数组的长度
    long long n2 = right - mid;    // 右子数组的长度
    // 将数据复制到临时数组 L 和 R
    for (long long i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (long long j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    long long i = 0; // 左子数组的索引
    long long j = 0; // 右子数组的索引
    long long k = left; // 主数组的索引
    // 合并两个临时数组
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i]; // 将较小的元素放入主数组
            i++;
        } else {
            arr[k] = R[j]; // 将较小的元素放入主数组
            j++;
        }
        k++;
    }
    // 将剩余元素复制到主数组
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 二分查找，用于查找点 p 在排序后的数组中的位置
long long binarySearch(Point p, long long a[], long long int b[], long long n) {
    long long mid, l = 0, r = n - 1, ans = 0; // 初始化二分查找的边界
    // 进行二分查找
    while (l < r) {
        mid = (r + l) >> 1; // 计算中间位置
        // 判断点 p 相对于线段的位置
        if (ToLeft(b[mid], a[mid], p) >= 0) {
            l = mid + 1; // 点在上方，调整左边界
        } else
            r = mid; // 点在下方，调整右边界
    }
    return l - 1; // 返回结果
}

int main() {
    long long n; // 点的数量
    scanf("%lld", &n); // 输入点的数量
    // 动态分配内存用于存储 x 和 y 坐标
    long long *Px = new long long[n + 1];
    long long *Py = new long long[n + 1];
    // 输入 x 坐标
    for (long long i = 0; i < n; ++i) {
        scanf("%lld", &Px[i]);
    }
    // 输入 y 坐标
    for (long long i = 0; i < n; ++i) {
        scanf("%lld", &Py[i]);
    }
    // 对 x 和 y 坐标进行合并排序
    mergeSort(Px, 0, n - 1);
    mergeSort(Py, 0, n - 1);
    long long m; // 查询点的数量
    scanf("%lld", &m); // 输入查询点的数量
    // 对每个查询点进行处理
    for (long long i = 0; i < m; ++i) {
        Point p;
        scanf("%lld %lld", &p.x, &p.y); // 输入查询点的坐标
        // 判断查询点是否在第一个点的左侧
        if (ToLeft(Py[0], Px[0], p) < 0) {
            printf("%lld\n", 0); 
            continue; 
        }
        // 判断查询点是否在最后一个点的右侧
        if (ToLeft(Py[n - 1], Px[n - 1], p) >= 0) {
            printf("%lld\n", n); // 输出 n
            continue;
        }
        // 使用二分查找找到点的索引
        long long pos = binarySearch(p, Px, Py, n);
        printf("%lld\n", pos + 1);
    }
    // 释放动态分配的内存
    delete[] Px;
    delete[] Py;
    return 0;
}
