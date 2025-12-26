#include <iostream>
#include "octal.h"

int main() {
    std::cout << " Octal class \n\n";
    
    // Демонстрация создания чисел
    Octal num1("1234");  // из строки
    Octal num2(3, 5);    // 3 цифры, каждая равна 5
    Octal num3{7, 6, 5}; // из списка инициализации
    Octal zero;          // по умолчанию - ноль
    
    std::cout << "Number 1 (from string): " << num1.toString() << std::endl;
    std::cout << "Number 2 (size 3, digit 5): " << num2.toString() << std::endl;
    std::cout << "Number 3 (from list): " << num3.toString() << std::endl;
    std::cout << "Zero: " << zero.toString() << std::endl;
    
    std::cout << "\nАрифм опреации\n\n";
    
    // Сложение
    Octal sum = num1.add(num3);
    std::cout << num1.toString() << " + " << num3.toString() 
              << " = " << sum.toString() << std::endl;
    
    // Вычитание
    Octal diff = num1.subtract(num3);
    std::cout << num1.toString() << " - " << num3.toString() 
              << " = " << diff.toString() << std::endl;
    
    // Умножение
    Octal product = num2.multiply(num3);
    std::cout << num2.toString() << " * " << num3.toString() 
              << " = " << product.toString() << std::endl;
    
    std::cout << "\nСравнение\n\n";
    
    // Сравнение
    std::cout << num1.toString() << " > " << num3.toString() << "? "
              << (num1.isGreaterThan(num3) ? "Yes" : "No") << std::endl;
    
    std::cout << num1.toString() << " < " << num3.toString() << "? "
              << (num1.isLessThan(num3) ? "Yes" : "No") << std::endl;
    
    std::cout << num1.toString() << " == " << num1.toString() << "? "
              << (num1.isEqual(num1) ? "Yes" : "No") << std::endl;
    
    std::cout << "\nС нулем\n\n";
    
    // Работа с нулем
    std::cout << "0 + Number 1 = " << zero.add(num1).toString() << std::endl;
    std::cout << "Number 1 - Number 1 = " << num1.subtract(num1).toString() << std::endl;
    std::cout << "0 * Number 1 = " << zero.multiply(num1).toString() << std::endl;
    
    // Демонстрация исключений
    std::cout << "\nИсключения\n\n";
    
    try {
        Octal invalid("128");  // цифра 8 недопустима в восьмеричной
        std::cout << "Не восьм" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "invalid argument: " << e.what() << std::endl;
    }
    
    try {
        Octal small("12");
        Octal large("345");
        Octal result = small.subtract(large);  // попытка вычесть большее из меньшего
        std::cout << "ошибка" << std::endl;
    } catch (const std::underflow_error& e) {
        std::cout << "неверно введены " << e.what() << std::endl;
    }
    
    std::cout << "\nЗавершено\n";
    
    return 0;
}