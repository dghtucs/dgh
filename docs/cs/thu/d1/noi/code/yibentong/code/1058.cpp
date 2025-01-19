#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double a, b, c;
    cin >> a >> b >> c;

    double discriminant = b * b - 4 * a * c;

    // Check for the nature of the discriminant
    if (discriminant < 0) {
        cout << "No answer!" << endl;  // No real solutions
    } else if (discriminant == 0) {
        // One solution (equal roots)
        double x = -b / (2 * a);
        cout << "x1=x2=" << fixed << setprecision(5) << x << endl;
    } else {
        // Two distinct solutions
        double sqrt_disc = sqrt(discriminant);
        double x1 = (-b + sqrt_disc) / (2 * a);
        double x2 = (-b - sqrt_disc) / (2 * a);

        // Output the roots in increasing order
        if (x1 > x2) swap(x1, x2); // Ensure x1 <= x2
        cout << "x1=" << fixed << setprecision(5) << x1 << ";x2=" << fixed << setprecision(5) << x2 << endl;
    }

    return 0;
}
