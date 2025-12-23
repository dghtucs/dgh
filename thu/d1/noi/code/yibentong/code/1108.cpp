#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;  // Read the number of dimensions (n)
    
    vector<int> a(n), b(n);
    
    // Read vector a
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Read vector b
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    int dot_product = 0;
    
    // Calculate dot product
    for (int i = 0; i < n; i++) {
        dot_product += a[i] * b[i];
    }
    
    // Output the result
    cout << dot_product << endl;
    
    return 0;
}
