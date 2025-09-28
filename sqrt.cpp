#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double number;
    cout << "Enter a positive number: ";
    cin >> number;

    double low, high;
    if (number >= 1) {
        low = 0;
        high = number;
    } else {
        low = 0;
        high = 1;
    }

    while ((high - low) >= 0.01) {
        double midpoint = (low + high) / 2.0;

        if (midpoint * midpoint > number) {
            high = midpoint;
        } else {
            low = midpoint;
        }
    }

    double result = (low + high) / 2.0;

    cout << fixed << setprecision(2);
    cout << "Square root of " << number << " = " << result << endl;

    return 0;
}

