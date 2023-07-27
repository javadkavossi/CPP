#include <iostream>
#include <vector>
#include <string>


// code-runner.exe && Cpp standard g++ > 11 && 
// Code-runner ==> Executor Map ===  "cpp": "cd $dir && g++ -std=c++11 $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}