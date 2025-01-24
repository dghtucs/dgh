#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    int M;
    cin >> M;  // Read the number of integers
    vector<long long> numbers(M);  // Create a vector to store the numbers
    
    // Read the sequence of numbers
    for (int i = 0; i < M; i++) {
        cin >> numbers[i];
    }

    // Find the maximum and minimum values
    long long max_value = *max_element(numbers.begin(), numbers.end());
    long long min_value = *min_element(numbers.begin(), numbers.end());
    long long sum = accumulate(numbers.begin(), numbers.end(),0);

    // Output the difference between the maximum and minimum values
    cout << sum - max_value << endl;

    return 0;
}
