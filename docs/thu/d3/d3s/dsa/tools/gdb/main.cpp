#include <iostream>
using namespace std;

int main() {
    cout << "Hello, DSA!" << endl;
    // qsort
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    qsort(arr, n, sizeof(int), [](const void* a, const void* b) {
        return (*(int*)a - *(int*)b);
    });
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}