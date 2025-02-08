#include <iostream>
#include <iomanip>  // For setprecision and fixed
using namespace std;

int main() {
    
    double d;

    cin >> d;
    printf("%f\n%.5f\n%e\n%g",d,d,d,d);

    return 0;
}
