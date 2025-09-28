#include <iostream>
using namespace std;

int main() {
    int n1, d1, n2, d2;
    char op;

    cout << "Enter numerator and denominator of first fraction: ";
    cin >> n1 >> d1;

    cout << "Enter numerator and denominator of second fraction: ";
    cin >> n2 >> d2;

    cout << "Choose operation (+, -, *, /): ";
    cin >> op;

    int num = 0, den = 1;

    if (op == '+') {
        num = n1 * d2 + n2 * d1;
        den = d1 * d2;
    }
    else if (op == '-') {
        num = n1 * d2 - n2 * d1;
        den = d1 * d2;
    }
    else if (op == '*') {
        num = n1 * n2;
        den = d1 * d2;
    }
    else if (op == '/') {
        num = n1 * d2;
        den = d1 * n2;
    }
    else {
        cout << "Invalid operation!\n";
        return 0;
    }

    int smaller = (num < den) ? num : den;
    if (smaller < 0) smaller = -smaller;
    int gcd = 1;
    for (int i = 1; i <= smaller; i++) {
        if (num % i == 0 && den % i == 0) {
            gcd = i;
        }
    }

    num = num / gcd;
    den = den / gcd;

    cout << "Result: " << num << "/" << den << endl;

    return 0;
}
