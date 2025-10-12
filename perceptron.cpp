#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double w = 0.0;
    double b = 0.0;
    int x = 3;
    double y = 0;
    double target = 14.0;
    double learningRate = 0.01;

    cout << fixed << setprecision(2);

    for (int i = 0; i < 1000; i++)
    {
        y = (w * x) + b;
        double error = target - y;

        w = w + (learningRate * error * x);
        b = b + (learningRate * error);

        if (i == 0 || i % 100 == 0)
        {
            cout << "Step " << i << ": " << "prediction = " << y << ", error = " << error << "\n";
        }
    }

    cout << "..." << "\n"
         << "Final prediction at x=3: " << y << "\n"
         << "Target value: " << target << "\n"
         << "Final w = " << w << ", b = " << b << "\n";
}