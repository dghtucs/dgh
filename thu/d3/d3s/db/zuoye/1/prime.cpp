#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void selectPrime(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int p = 2; p <= sqrt(n); ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }
    int count = 0;
    for (int p = 2; p <= n; ++p) {
        if (isPrime[p]) {
            count++;
            cout << p << (count%6==0 ? "\n" : " ");
        }
    }
    cout << endl << "总共有 " << count << " 个素数" << endl;
}
int main() {
    const int limit = 300;
    selectPrime(limit);
    return 0;
}
