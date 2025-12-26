#include "octal.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>

namespace octal {
    // Валидация восьмеричной цифры
    void Octal::validateDigit(unsigned char digit) const {
        if (digit > 7) {
            throw std::invalid_argument("Invalid octal digit: must be 0-7");
        }
    }
    
    // Удаление ведущих нулей
    void Octal::removeLeadingZeros() {
        // Если пусто, ничего не делаем
        if (digits.size() == 0) {
            digits = Array::Array(1, 0);
            return;
        }
        
        // Создаем вектор цифр
        std::vector<unsigned char> tempDigits;
        for (size_t i = 0; i < digits.size(); ++i) {
            unsigned char d = digits.at(i);
            // Преобразуем символ в число если нужно
            if (d >= '0' && d <= '7') {
                tempDigits.push_back(d - '0');
            } else {
                tempDigits.push_back(d);
            }
        }
        
        // Удаляем ведущие нули с конца (младшие разряды в начале вектора)
        while (tempDigits.size() > 1 && tempDigits.back() == 0) {
            tempDigits.pop_back();
        }
        
        // Если все цифры нули
        if (tempDigits.empty() || (tempDigits.size() == 1 && tempDigits[0] == 0)) {
            digits = Array::Array(1, 0);
            return;
        }
        
        // Создаем новую строку
        std::string cleanStr;
        for (auto it = tempDigits.rbegin(); it != tempDigits.rend(); ++it) {
            cleanStr += std::to_string(*it);
        }
        
        digits = Array::Array(cleanStr);
    }
    
    // Конструктор по умолчанию
    Octal::Octal() : digits(1, 0) {}
    
    // Конструктор с размером и значением
    Octal::Octal(const size_t& n, unsigned char t) : digits(n, t) {
        validateDigit(t);
        removeLeadingZeros();
    }
    
    // Конструктор со списком инициализации
    Octal::Octal(const std::initializer_list<unsigned char>& list) : digits(list) {
        for (auto digit : list) {
            validateDigit(digit);
        }
        removeLeadingZeros();
    }
    
    // Конструктор из строки
    Octal::Octal(const std::string& str) {
        if (str.empty()) {
            digits = Array::Array(1, 0);
            return;
        }
        
        // Проверяем каждый символ
        for (char c : str) {
            if (c < '0' || c > '7') {
                throw std::invalid_argument("Invalid octal digit in string");
            }
        }
        
        // Удаляем ведущие нули из строки
        size_t start = 0;
        while (start < str.length() - 1 && str[start] == '0') {
            start++;
        }
        
        std::string cleanStr = str.substr(start);
        digits = Array::Array(cleanStr);
    }
    
    // Конструктор копирования
    Octal::Octal(const Octal& other) : digits(other.digits) {}
    
    // Конструктор перемещения
    Octal::Octal(Octal&& other) noexcept : digits(std::move(other.digits)) {
        // Оставляем other в валидном состоянии
        other.digits = Array::Array(1, 0);
    }
    
    // Оператор присваивания копированием
    Octal& Octal::operator=(const Octal& other) {
        if (this != &other) {
            digits = other.digits;
        }
        return *this;
    }
    
    // Оператор присваивания перемещением
    Octal& Octal::operator=(Octal&& other) noexcept {
        if (this != &other) {
            digits = std::move(other.digits);
            other.digits = Array::Array(1, 0);
        }
        return *this;
    }
    
    // Деструктор
    Octal::~Octal() noexcept {}
    
    // Сложение
    Octal Octal::add(const Octal& other) const {
        // Получаем строки обоих чисел
        std::string str1 = toString();
        std::string str2 = other.toString();
        
        // Делаем строки одинаковой длины
        size_t maxLen = std::max(str1.length(), str2.length());
        while (str1.length() < maxLen) str1 = "0" + str1;
        while (str2.length() < maxLen) str2 = "0" + str2;
        
        std::string result;
        int carry = 0;
        
        // Складываем с конца
        for (int i = maxLen - 1; i >= 0; --i) {
            int sum = (str1[i] - '0') + (str2[i] - '0') + carry;
            result = std::to_string(sum % 8) + result;
            carry = sum / 8;
        }
        
        // Если остался перенос
        if (carry > 0) {
            result = std::to_string(carry) + result;
        }
        
        return Octal(result);
    }
    
    // Вычитание
    Octal Octal::subtract(const Octal& other) const {
        if (isLessThan(other)) {
            throw std::underflow_error("Result would be negative");
        }
        
        if (isEqual(other)) {
            return Octal();
        }
        
        std::string str1 = toString();
        std::string str2 = other.toString();
        
        // Делаем строки одинаковой длины
        size_t maxLen = std::max(str1.length(), str2.length());
        while (str1.length() < maxLen) str1 = "0" + str1;
        while (str2.length() < maxLen) str2 = "0" + str2;
        
        std::string result;
        int borrow = 0;
        
        // Вычитаем с конца
        for (int i = maxLen - 1; i >= 0; --i) {
            int digit1 = (str1[i] - '0') - borrow;
            int digit2 = (str2[i] - '0');
            
            if (digit1 < digit2) {
                digit1 += 8;
                borrow = 1;
            } else {
                borrow = 0;
            }
            
            result = std::to_string(digit1 - digit2) + result;
        }
        
        // Удаляем ведущие нули
        size_t pos = 0;
        while (pos < result.length() - 1 && result[pos] == '0') {
            pos++;
        }
        result = result.substr(pos);
        
        return Octal(result);
    }
    
    // Умножение
    Octal Octal::multiply(const Octal& other) const {
        if (isZero() || other.isZero()) {
            return Octal();
        }
        
        // Получаем строки
        std::string str1 = toString();
        std::string str2 = other.toString();
        
        // Векторы для хранения цифр в обратном порядке
        std::vector<int> num1, num2;
        for (int i = str1.length() - 1; i >= 0; --i) {
            num1.push_back(str1[i] - '0');
        }
        for (int i = str2.length() - 1; i >= 0; --i) {
            num2.push_back(str2[i] - '0');
        }
        
        // Результат умножения
        std::vector<int> result(num1.size() + num2.size(), 0);
        
        // Умножаем
        for (size_t i = 0; i < num1.size(); i++) {
            for (size_t j = 0; j < num2.size(); j++) {
                result[i + j] += num1[i] * num2[j];
                result[i + j + 1] += result[i + j] / 8;
                result[i + j] %= 8;
            }
        }
        
        // Убираем ведущие нули
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }
        
        // Преобразуем в строку в правильном порядке
        std::string resultStr;
        for (int i = result.size() - 1; i >= 0; i--) {
            resultStr += std::to_string(result[i]);
        }
        
        return Octal(resultStr);
    }
    
    // Сравнение: больше чем
    bool Octal::isGreaterThan(const Octal& other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() > other.digits.size();
        }
        
        for (size_t i = 0; i < digits.size(); ++i) {
            unsigned char d1 = digitAt(i);
            unsigned char d2 = other.digitAt(i);
            if (d1 != d2) {
                return d1 > d2;
            }
        }
        
        return false;
    }
    
    // Сравнение: меньше чем
    bool Octal::isLessThan(const Octal& other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() < other.digits.size();
        }
        
        for (size_t i = 0; i < digits.size(); ++i) {
            unsigned char d1 = digitAt(i);
            unsigned char d2 = other.digitAt(i);
            if (d1 != d2) {
                return d1 < d2;
            }
        }
        
        return false;
    }
    
    // Сравнение: равно
    bool Octal::isEqual(const Octal& other) const {
        if (digits.size() != other.digits.size()) {
            return false;
        }
        
        for (size_t i = 0; i < digits.size(); ++i) {
            if (digitAt(i) != other.digitAt(i)) {
                return false;
            }
        }
        
        return true;
    }
    
    // Преобразование в строку
    std::string Octal::toString() const {
        std::string result;
        for (size_t i = 0; i < digits.size(); ++i) {
            unsigned char d = digits.at(i);
            // Преобразуем в символ если нужно
            if (d >= 0 && d <= 7) {
                result += static_cast<char>('0' + d);
            } else {
                result += d;
            }
        }
        return result;
    }
    
    // Размер числа
    size_t Octal::size() const noexcept {
        return digits.size();
    }
    
    // Проверка на ноль
    bool Octal::isZero() const noexcept {
        std::string str = toString();
        return str == "0" || str.empty();
    }
    
    // Получение цифры по позиции (0 - младший разряд)
    unsigned char Octal::digitAt(size_t position) const {
        if (position >= digits.size()) {
            return 0;
        }
        
        unsigned char d = digits.at(digits.size() - 1 - position);
        // Преобразуем символ в число если нужно
        if (d >= '0' && d <= '7') {
            return d - '0';
        }
        return d;
    }
}