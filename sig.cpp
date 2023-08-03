#include <iostream>
#include <string>

// ==== get Message 
std::string getMessage()
{
    std::string message;
    std::cout << "plase enter a Massage ... ";
    std::cin >> message;
    return message;
}

// ------------------------

int main()
{
    std::cout << getMessage();
    return 0;
}