#include <iostream>
#include <vector>
#include <array>
using namespace std;

// checks if the user input follows the valid format
// accepts help quit history or an expression with operator number number
bool isValidInput(string s)
{
    if (s != "help" && s != "quit" && s != "history")
    {
        // input must be at least 5 characters like + 2 3
        if (s.length() < 5)
        {
            cout << "Please follow the format given in help-usage!" << endl;
            return false;
        }

        // first character must be a valid operator
        if (s[0] != '+' && s[0] != '-' && s[0] != '*' && s[0] != '/')
        {
            cout << "Invalid operator!" << endl;
            return false;
        }

        // second character must be a space
        if (s[1] != ' ')
        {
            return false;
        }

        // find spaces to extract numbers
        size_t firstspace = s.find(' ');
        size_t secondspace = s.find(' ', firstspace + 1);

        // substrings for first and second numbers
        string firstValue = s.substr(firstspace + 1, secondspace - (firstspace + 1));
        string secondValue = s.substr(secondspace + 1);

        // check if both numbers are digits only
        for (char c : firstValue)
        {
            if (!isdigit(c))
                return false;
        }
        for (char c : secondValue)
        {
            if (!isdigit(c))
                return false;
        }
    }

    return true;
}

// prints the help information and shows available commands
void showHelp()
{
    cout << "Simple Command-Line Calculator\n";
    cout << "Type 'help' for a list of commands.\n\n";

    cout << "Usage:\n";
    cout << "  <operator> <num1> <num2>\n\n";

    cout << "Description:\n";
    cout << "  Perform basic arithmetic operations or run utility commands.\n\n";

    cout << "Operators:\n";
    cout << "  +, -, *, /        perform arithmetic between two numbers\n";
    cout << "                    Example: + 5 3    ->    8\n\n";

    cout << "Commands:\n";
    cout << "  history           show history of all previous operations\n";
    cout << "  help              display this help message\n";
    cout << "  quit              exit the program\n";
}

// gets input from user and validates it
// returns only valid input
string userInput()
{
    string input;

    while (true)
    {
        cout << "> ";
        getline(cin, input);

        // print help when user types help
        if (input == "help")
        {
            showHelp();
            continue;
        }

        // only return when input is valid
        if (isValidInput(input))
            return input;
    }
}

// splits the expression into operator and two numbers
// returns vector containing these three parts
vector<string> parseString(string values)
{
    vector<string> userInput;

    size_t firstspace = values.find(' ');
    size_t secondspace = values.find(' ', firstspace + 1);

    string operation = values.substr(0, firstspace);
    string firstValue = values.substr(firstspace + 1, secondspace - (firstspace + 1));
    string secondValue = values.substr(secondspace + 1);

    userInput.push_back(operation);
    userInput.push_back(firstValue);
    userInput.push_back(secondValue);

    return userInput;
}

// these functions perform the four arithmetic operations
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divideInt(int a, int b) { return a / b; }

int main()
{
    cout << "Simple Command-Line Calculator!" << endl;
    cout << "Type 'help' for a list of commands." << endl;

    // history stores previous operations in the form
    // first number operator as int second number result
    vector<array<int, 4>> history;

    while (true)
    {
        string input = userInput();

        // quit ends the loop
        if (input == "quit")
            break;

        // show history and skip to next loop
        if (input == "history")
        {
            for (int i = 0; i < history.size(); i++)
            {
                cout << history[i][0] << " "
                     << static_cast<char>(history[i][1]) << " "
                     << history[i][2] << " = " << history[i][3] << endl;
            }
            continue;
        }

        // split the input into operator and numbers
        vector<string> operationString = parseString(input);
        char op = operationString[0][0];

        int firstNumber;
        int secondNumber;
        int result;

        // convert number strings to integers
        firstNumber = stoi(operationString[1]);
        secondNumber = stoi(operationString[2]);

        // perform the correct operation
        switch (op)
        {
        case '+':
            result = add(firstNumber, secondNumber);
            break;

        case '-':
            result = subtract(firstNumber, secondNumber);
            break;

        case '*':
            result = multiply(firstNumber, secondNumber);
            break;

        case '/':
            // check division by zero
            if (secondNumber == 0)
            {
                cout << "Error! Division by zero not possible." << endl;
                continue;
            }
            else
            {
                result = divideInt(firstNumber, secondNumber);
            }
            break;
        }

        // store this calculation in the history vector
        // operator is stored as its ascii integer value
        array<int, 4> entry = {firstNumber, static_cast<int>(op), secondNumber, result};
        history.push_back(entry);

        // print result of this calculation
        cout << result << endl;
    }
}
