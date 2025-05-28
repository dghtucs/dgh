#include <iostream>
#include <cmath>    // For sqrt() function
#include <iomanip>  // For setprecision
using namespace std;

int main() {
    double a, b, c;
    // Input the three sides of the triangle
    cin >> a >> b >> c;
    
    // Calculate the semi-perimeter p
    double p = (a + b + c) / 2;
    
    // Calculate the area using Heron's formula
    double area = sqrt(p * (p - a) * (p - b) * (p - c));
    
    // Output the area, rounded to 3 decimal places
    cout << fixed << setprecision(3) << area << endl;

    return 0;
}
