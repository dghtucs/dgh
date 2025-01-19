#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double N;
    cin >> N;
    
    double result;

    if (N >= 0 && N < 5) {
        result = -1.0 * N + 2.5;
    } else if (N >= 5 && N < 10) {
        result = 2 - 1.5 * (N - 3) * (N - 3);
    } else if (N >= 10 && N < 20) {
        result = N / 2 - 1.5;
    }

    cout << fixed << setprecision(3) << result << endl;

    return 0;
}
