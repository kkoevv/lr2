#include <iostream>
#include <string>
#include "octal.hpp"

int main() {
    std::string input1, input2;
    
    std::cout << "Enter first octal number: ";
    std::cin >> input1;
    
    std::cout << "Enter second octal number: ";
    std::cin >> input2;
    
    try {
        octal::Octal num1(input1);
        octal::Octal num2(input2);
        
        std::cout << "\nResults:\n";
        std::cout << "Number 1: " << num1.toString() << std::endl;
        std::cout << "Number 2: " << num2.toString() << std::endl;
        
        octal::Octal sum = num1.add(num2);
        std::cout << "Sum: " << sum.toString() << std::endl;
        
        octal::Octal diff = num1.subtract(num2);
        std::cout << "Difference: " << diff.toString() << std::endl;
        
        octal::Octal product = num1.multiply(num2);
        std::cout << "Product: " << product.toString() << std::endl;
        
        std::cout << "Is num1 > num2? " << (num1.isGreaterThan(num2) ? "Yes" : "No") << std::endl;
        std::cout << "Is num1 < num2? " << (num1.isLessThan(num2) ? "Yes" : "No") << std::endl;
        std::cout << "Is num1 == num2? " << (num1.isEqual(num2) ? "Yes" : "No") << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}