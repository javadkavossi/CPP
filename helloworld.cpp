#include <iostream>

int add(int a, int b) {
    return a + b;
}

int main() {
    int num1, num2;

    std::cout << "Enter the first number: ";
    std::cin >> num1;

    std::cout << "Enter the second number: ";
    std::cin >> num2;

    int result = add(num1, num2);
    std::cout << "The sum of " << num1 << " and " << num2 << " is: " << result << std::endl;

    return 0;
}
