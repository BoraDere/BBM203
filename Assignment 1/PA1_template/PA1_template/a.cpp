#include <iostream>

void a(std::string &x, std::string &y);

int main() { 
    
    std::string x = "Hello";
    std::string y = "World";

    a(x, y);
    return 0;
}

void a(std::string &x, std::string &y) {
    std::cout << &x << "\n" << &y << std::endl;
}