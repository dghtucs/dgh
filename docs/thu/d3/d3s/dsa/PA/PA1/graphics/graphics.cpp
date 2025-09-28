#include <iostream>

using namespace std;
long long L[200005], R[200005];

struct Point {
    long long x, y;
};




long long ToLeft(long long ay,long long bx,Point c) {
    return (bx - 0) * (c.y - ay) - (c.x - 0) * (0 - ay);
}
void mergeSort(long long arr[], long long left, long long right);
void merge(long long arr[], long long left, long long mid, long long right);
void mergeSort(long long arr[], long long left, long long right) {
    if (left < right) {
        long long mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}
void merge(long long arr[], long long left, long long mid, long long right) {
    long long n1 = mid - left + 1; 
    long long n2 = right - mid;
    


    for (long long i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (long long j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];


    long long i = 0;
    long long j = 0;
    long long k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

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

long long binarySearch(Point p, long long a[],long long int b[], long long n){
    

    long long mid,l = 0,r = n-1,ans = 0;
    while(l < r)
    {
        mid = (r + l) >> 1;
        if (ToLeft(b[mid],a[mid], p) >= 0)
        {
            l = mid + 1;
        }
        else
            r = mid;
    }
    return l-1;
}

int main() {


    long long n;
    scanf("%lld",&n);

    long long *Px = new long long[n+1];
    long long *Py = new long long[n+1];
    for (long long i = 0; i < n; ++i) {
        scanf("%lld",&Px[i]);
    }
    
    for (long long i = 0; i < n; ++i) {
        scanf("%lld",&Py[i]);
    }
    
    mergeSort(Px,0,n-1);
    mergeSort(Py,0,n-1);
    

    long long m;
    scanf("%lld",&m);

    for (long long i = 0; i < m; ++i) {
        Point p;
        scanf("%lld %lld",&p.x,&p.y);
        if (ToLeft(Py[0],Px[0], p) < 0){
            printf("%lld\n",0);
            continue;
        }
        if (ToLeft(Py[n-1],Px[n-1], p) >= 0){
            printf("%lld\n",n);
            continue;
        }

        long long pos = binarySearch(p,Px,Py,n);
        printf("%lld\n",pos+1);
    }


    delete[] Px;
    delete[] Py;

    return 0;
}
