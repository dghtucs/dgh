# 实验报告

## 解题思路

首先我将点和线段抽象化，便于理解
```cpp
struct Point {
    long long x, y;
};


struct Segment {
    Point p1, p2;
};
```
这样可以直观地理解问题，讨论交点的情况
因为n条线段是相互之间没有交点的，所以只需要对x轴和y轴的截距坐标进行排序，即可得到线段端点的坐标。
判断某一个点和线段的相对位置时，使用了向量叉积运算，假设线段AB，需要判断点P和线段的相对位置

$$
if \mathbf{AB} \times \mathbf{AP} > 0
$$
则点P在线段AB的右上方，如果＜0则在左下方，如果叉积结果为零，那说明P就在线段AB之上。
```cpp
long long ToLeft(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
```

接下来，只需要通过二分的方法，逐步检测最接近P点的交点存在于哪一条线段上即可。
```cpp
int binarySearch(Point p, Segment* segments, int n){
    int mid,l = 0,r = n-1,ans = 0;
    while(l <= r)
    {
        mid = l + (r - l) / 2;
        if (ToLeft(segments[mid].p1, segments[mid].p2, p) >= 0)
        {
            ans = mid,l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return ans;
}
```
我在debug的过程中，总是有三个点会TLE，不知道为什么，最后发现我在一个隐藏的地方cin了200000*2次数据，导致非常慢，我在发现之后改为scanf就顺利通过了，这让我直观地体会到cin，cout地方便易用是在牺牲性能的代价下的。


## 时空复杂度分析
### 时间复杂度
合并排序（Merge Sort）：
合并排序的时间复杂度为 O(n log n)，其中 n 是待排序数组的大小。在 mergeSort 函数中，分治的过程会递归进行，并且合并操作的复杂度为 O(n)。在代码中，我们对两个数组 Px 和 Py 进行了排序，因此总的排序时间复杂度为 O(n log n)。
二分查找（Binary Search）：
在 binarySearch 函数中，二分查找的时间复杂度为 O(log n)。这是因为每次查找都会将搜索范围减半。
总体复杂度：
合并排序和二分查找的总体时间复杂度为 O(n log n + m log n)，其中 m 是查询点的数量。对于每个查询点，都执行一次二分查找，因此总的时间复杂度是 O(n log n + m log n)。
 
### 空间复杂度
合并排序的临时数组：
在合并过程中使用了两个全局数组 L 和 R，每个数组的大小为 O(n)，因此空间复杂度为 O(n)。
动态分配的数组：
通过 new 动态分配的数组 Px 和 Py 也占用 O(n) 的空间。
总体复杂度：
综合考虑，整体的空间复杂度为 O(n)，这是由排序和动态分配的数组所决定的。
### 总结
时间复杂度：O(n log n + m log n)
空间复杂度：O(n)












