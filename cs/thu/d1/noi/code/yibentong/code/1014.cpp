#include <iostream>
#include <iomanip>  // For setting precision
using namespace std;

int main() {
    double r;
    // Input the radius
    cin >> r;
    
    // Define the value of Pi
    const double pi = 3.14159;
    
    // Calculate the diameter, circumference, and area
    double diameter = 2 * r;
    double circumference = 2 * pi * r;
    double area = pi * r * r;
    
    // Output the results with 4 decimal places
    cout << fixed << setprecision(4) << diameter << " " 
         << circumference << " " << area << endl;

    return 0;
}
