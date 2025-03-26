#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int evenSum = 0; // To store the sum of even numbers
    int oddSum = 0;  // To store the sum of odd numbers

    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            evenSum += i; // Add to even sum if the number is even
        } else {
            oddSum += i;  // Add to odd sum if the number is odd
        }
    }

    // Output the even sum and odd sum separated by a space
    cout << evenSum << " " << oddSum << endl;

    return 0;
}
