#include <iostream>
#include <iomanip>  // For setting precision
using namespace std;

int main() {
    double r1, r2;
    // Input the two resistances
    cin >> r1 >> r2;
    
    // Calculate the parallel resistance using the formula
    double R = 1.0 / (1.0 / r1 + 1.0 / r2);
    
    // Output the result with 2 decimal places
    cout << fixed << setprecision(2) << R << endl;

    return 0;
}
