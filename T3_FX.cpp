#include <iostream>

void doPrint()
{
    std::cout << "enter doprint ";
}

int fA()
{
    int a{};
    a = 123 + 12;

    return a;
}

int main()
{
    std::cout << "plese inter a number : \n";
    doPrint();
    std::cout << " \n exit:" << fA();
    return 0;
}