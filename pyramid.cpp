#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int s = 0; s < n - i; s++) {
            cout << "  ";
        }

        for (int k = 1; k <= i; k++) {
            cout << k << " ";
        }

        for (int k = i - 1; k >= 1; k--) {
            cout << k << " ";
        }

        cout << "\n";
    }

    return 0;
}
