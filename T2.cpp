#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

// check if a string contains only digit characters
bool isAllDigits(string number)
{
    for (char c : number)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

// validate the submission files for a lab
// returns true when zip file name and task files match the expected patterns
bool valid_submission(int labNumber, int erp, const std ::vector<std ::string> &files)
{
    bool isValidTask = true;
    bool allTasksValid = true;
    int counter = 0;
    int total = 1;

    // first file is expected to be the zip file
    string zipFile = files[0];
    // expected zip file name like lab8_12345.zip
    string expectedZip = "lab" + to_string(labNumber) + "_" + to_string(erp) + ".zip";

    bool isZipValid = (zipFile == expectedZip);
    if (isZipValid)
    {
        counter++;
    }

    cout << "Validating submission: " << zipFile << endl;
    string zipResult = isZipValid ? "pass" : "fail";
    // print the zip file check result aligned with setw
    cout << left << "- " << setw(20) << zipFile << zipResult << endl;

    // check remaining files which should be task files
    for (int i = 1; i < files.size(); i++)
    {
        total++;
        bool isThisTaskValid = true;
        isValidTask = true;

        string task = files[i];

        // task file must start with task
        if (task.rfind("task", 0) != 0)
        {
            isThisTaskValid = false;
        }
        else
        {
            int dotpos = task.find('.');
            // file must have .cpp extension
            if (dotpos == string::npos || task.substr(dotpos) != ".cpp")
            {
                isThisTaskValid = false;
            }
            else
            {
                // extract the number part after task and before dot
                string taskNumber = task.substr(4, dotpos - 4);
                // task number must not be empty must not start with 0 and must be digits only
                if (taskNumber.empty() || taskNumber[0] == '0' || !isAllDigits(taskNumber))
                    isThisTaskValid = false;
            }
        }

        // print each task check result
        cout << left
             << "- " << setw(20) << task
             << (isThisTaskValid ? "pass" : "fail")
             << endl;

        if (!isThisTaskValid)
        {
            isValidTask = false;
            allTasksValid = false;
        }
        else {
            counter ++;
        }

        // increment counter only when still valid so far
    }

    // print summary of how many passed
    cout << "Summary for " << zipFile << ":  " << counter << "/" << total << " passed" << endl;

    if (isZipValid && allTasksValid)
        return true;

    return false;
}

int main()
{
    // sample list of files to validate
    vector<string> valid_submission_file = {
        "lab8_12345.zip",
        "task1.cpp",
        "task02.cpp",
        "task3!.cpp",
        "task4.cpp"};

    vector<string> invalid_zip_case = {
        "lab_12345.zip",
        "task1.cpp",
        "task2.cpp"};

    vector<string> invalid_taskname_case = {
        "lab8_12345.zip",
        "taks1.cpp", // misspelled
        "task2.cpp"};

    vector<string> special_char_case = {
        "lab8_12345.zip",
        "task1.cpp",
        "task3!.cpp", // special character
        "task4.cpp"};

    vector<vector<string> *> allTests = {
        &valid_submission_file,
        &invalid_zip_case,
        &invalid_taskname_case,
        &special_char_case};

    for (int i = 0; i < allTests.size(); i++)
    {
        bool isParseOk = true;
        string zipFile;

        vector<string> &file = *allTests[i];

        if (file.empty())
        {
            isParseOk = false;
        }
        else
        {
            zipFile = file[0];
        }

        if (zipFile.size() < 4)
        {
            isParseOk = false;
        }

        if (zipFile.rfind("lab", 0) != 0)
        {
            isParseOk = false;
        }

        int labNumber = 0;
        int erpNumber = 0;

        // find positions of underscore and dot in the zip file name
        size_t underscorepos = zipFile.find("_");
        size_t dotpos = zipFile.find(".");

        // ensure both underscore and dot exist and underscore comes before dot
        if (underscorepos == string::npos || dotpos == string::npos || (underscorepos > dotpos))
        {
            isParseOk = false;
        }

        // extract lab number and erp number from the zip file name when parsing is ok
        if (isParseOk)
        {
            string labNumberStr = zipFile.substr(3, underscorepos - 3);
            string erpNumberStr = zipFile.substr(underscorepos + 1, dotpos - (underscorepos + 1));

            // both parts must be non empty and contain only digits
            if (isAllDigits(labNumberStr) && isAllDigits(erpNumberStr) && !labNumberStr.empty() && !erpNumberStr.empty())
            {
                labNumber = stoi(labNumberStr);
                erpNumber = stoi(erpNumberStr);
            }
        }

        // call the validator with parsed lab and erp numbers and the file list
        valid_submission(labNumber, erpNumber, file);
    }

    return 0;
}
