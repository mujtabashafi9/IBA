#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// compare two characters in a case insensitive way
bool compareChar(char a, char b)
{
    return tolower(a) < tolower(b);
}

// sort first n characters of the string in place
// if n is negative or larger than length then sort whole string
void sort_string_inplace(string &str, int n = -1)
{
    // get current length of string
    int len = str.length();

    // adjust n to not exceed length
    if (n <= 0 || n > len)
        n = len;

    // selection sort for first n characters
    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; ++j)
        {
            if (compareChar(str[j], str[minIndex]))
            {
                minIndex = j;
            }
        }

        // swap when a smaller character is found
        if (minIndex != i)
        {
            char temp = str[i];
            str[i] = str[minIndex];
            str[minIndex] = temp;
        }
    }
}

// return a new sorted string leaving original unchanged
string sort_string(const string &s, int n = -1)
{
    string copy = s;
    sort_string_inplace(copy, n);
    return copy;
}

int main()
{
    string input;

    cout << "Enter a string: ";
    getline(cin, input);

    // do not accept empty input
    if (input.empty())
    {
        cout << "Input string can not be empty" << endl;
        return 1;
    }

    // allow only letters and spaces
    for (char c : input)
    {
        if (!isalpha(c) && c != ' ')
        {
            cerr << "String must contain letters only" << endl;
            return 1;
        }
    }

    int N;
    cout << "Enter N negative to sort the whole string: ";
    cin >> N;

    // check integer input
    if (!cin)
    {
        cout << "Enter a valid integer" << endl;
        return 1;
    }

    // show result when returning a new string
    string sorted_new = sort_string(input, N);
    cout << "Sorted string new " << sorted_new << endl;

    // show result when sorting the string in place
    sort_string_inplace(input, N);
    cout << "Sorted string in place " << input << endl;

    return 0;
}
