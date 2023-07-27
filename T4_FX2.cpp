#include <iostream>

int inputA()
{
    std::cout << "plase enter a number A : ";
    int number{};
    std::cin >> number;
    return number;
}

int inputB()
{
    std::cout << "plase enter a number B : ";
    int number{};
    std::cin >> number;
    return number;
}

void cal(int a, int b)
{
    int c{};
    c = a * b;
    std::cout << "number is : " << c;
}

int main()
{
    cal(inputA(), inputB());
    return 0;
}