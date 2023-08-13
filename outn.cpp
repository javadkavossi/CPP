#include <iostream>
#include <string>
using namespace std;

// ANSI Escape Code for Red Text
const string RED_TEXT = "\033[31m";
const string RESET_COLOR = "\033[0m";

int main()
{
    string input;

    cout << "Please enter a string: ";
    cin >> input;

    cout << "Modified string with red 'v': ";

    for (char c : input) {
        if (c == 'v' || c == 'V') {
            cout << RED_TEXT << c << RESET_COLOR;
        } else {
            cout << c;
        }
    }

    cout << endl;

    return 0;
}
