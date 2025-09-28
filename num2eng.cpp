#include <iostream>
using namespace std;

int main()
{

    int amount = 0;
    // input
    cout << "Enter an amount in figures: ";
    cin >> amount;

    // 999,999 - -999,999
    // unit, ten, hundred, thousandth, ten thousandth, hundred thousand

    bool isNegative;

    if (amount < 0)
    {
        isNegative = true;
        amount = -amount;
    }
    else
    {
        isNegative = false;
    }

    int amountLength = to_string(amount).length();

        int *nums = new int[amountLength]();

    string numsEng[10] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string scales[2] = {"thousand", "hundred"};
    string teens[10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    string tens[10] = {"", "", "twenty", "thirty", "forty", "fifty",
                       "sixty", "seventy", "eighty", "ninety"};

    // Loop to extract numbers
    for (int i = 0; i < amountLength; i++)
    {
        nums[i] = amount % 10;
        amount /= 10;
    }

    // 41020
    // fourty one thousand twenty
    // 17020
    // seventeen thousand twenty

    string printNum = "";

    if (isNegative)
    {
        printNum += "-";
    }

    if (amountLength == 0) {
        cout << "zero";
    }
    
    if (amountLength == 6)
    {
        if (nums[5] != 0)
        {
            printNum += numsEng[nums[5]] + " hundred ";
        }
    }
    if (amountLength >= 4)
    {
        if (nums[4] != 0)
        {
            if (nums[4] == 1)
            {
                printNum += teens[nums[3]] + " thousand ";
            }
            else
            {
                printNum += tens[nums[4]] + " " + numsEng[nums[3]] + " thousand ";
            }
        }
        else
        {
            printNum += numsEng[nums[3]] + " thousand ";
        }
    }
    if (nums[2] != 0)
    {
        printNum += numsEng[nums[2]] + " hundred ";
    }
    if (nums[1] != 0)
    {
        if (nums[1] == 1)
        {
            printNum += teens[nums[0]];
        }
        else
        {
            printNum += tens[nums[1]] + " " + numsEng[nums[0]];
        }
    }
    else
    {
        printNum += numsEng[nums[0]];
    }

    cout << printNum;

    cout << "\n";
    return 0;
}