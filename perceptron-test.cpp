#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double w = 4.2;
    double b = 1.4;
    double y = 0;
    int corrCount = 0;

    int x[10] = {};
    cout << "Enter 10 values for x: ";

    for (int i = 0; i < 10; i++)
    {
        cin >> x[i];
    }

    for (int i = 0; i < 10; i++)
    {
        int xi = x[i];
        double trueTarget = 2.0 * (xi * xi) - 4.0;

        y = (w * xi) + b;
        double error = trueTarget - y;

        cout << "x: " << xi
             << ", Current target: " << trueTarget
             << ", Perceptron's guess: " << y << "\n";

        if (fabs(y - trueTarget) <= 1.0)
        {
            cout << "Correct" << "\n";
            corrCount++;
        }
        else
        {
            cout << "Incorrect" << "\n";
        }
    }
    cout << "\n";

    cout << "Accuracy: " << (corrCount / 10.0) * 100 << "%" << "\n";

    return 0;
}