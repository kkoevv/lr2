#include "octal.h"
#include <algorithm>
#include <stdexcept>

// Валидация восьмеричной цифры
void Octal::validateDigit(unsigned char digit) const {
    if (digit > 7) {
        throw std::invalid_argument("0-7");
    }
}

// Удаление ведущих нулей
void Octal::removeLeadingZeros() {
    auto it = digits.begin();
    while (it != digits.end() - 1 && *it == 0) {
        ++it;
    }
    digits.erase(digits.begin(), it);
    
    if (digits.empty()) {
        digits.push_back(0);
    }
}

// Конструктор по умолчанию
Octal::Octal() : digits{0} {}

// Конструктор с размером и значением
Octal::Octal(size_t n, unsigned char t) : digits(n, t) {
    validateDigit(t);
    removeLeadingZeros();
}

// Конструктор со списком инициализации
Octal::Octal(const std::initializer_list<unsigned char>& list) 
    : digits(list.begin(), list.end()) {
    for (auto digit : list) {
        validateDigit(digit);
    }
    removeLeadingZeros();
}

// Конструктор из строки
Octal::Octal(const std::string& str) {
    if (str.empty()) {
        digits.push_back(0);
        return;
    }
    
    for (char c : str) {
        if (c < '0' || c > '7') {
            throw std::invalid_argument("не восьемичные");
        }
        digits.push_back(static_cast<unsigned char>(c - '0'));
    }
    
    removeLeadingZeros();
}

// Сложение
Octal Octal::add(const Octal& other) const {
    std::vector<unsigned char> result;
    size_t maxSize = std::max(digits.size(), other.digits.size());
    
    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize || carry > 0; ++i) {
        unsigned char d1 = digitAt(i);
        unsigned char d2 = other.digitAt(i);
        unsigned char sum = d1 + d2 + carry;
        
        result.push_back(sum % 8);
        carry = sum / 8;
    }
    
    // Переворачиваем результат (младший разряд в конце)
    std::reverse(result.begin(), result.end());
    
    // Создаем строку для конструктора
    std::string resultStr;
    for (auto d : result) {
        resultStr += std::to_string(d);
    }
    
    return Octal(resultStr);
}

// Вычитание
Octal Octal::subtract(const Octal& other) const {
    if (isLessThan(other)) {
        throw std::underflow_error("отр рез");
    }
    
    std::vector<unsigned char> result;
    size_t maxSize = digits.size();
    
    unsigned char borrow = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        int d1 = digitAt(i);
        int d2 = other.digitAt(i);
        int diff = d1 - d2 - borrow;
        
        if (diff < 0) {
            diff += 8;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.push_back(static_cast<unsigned char>(diff));
    }
    
    // Удаляем ведущие нули
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    
    // Переворачиваем результат
    std::reverse(result.begin(), result.end());
    
    // Создаем строку
    std::string resultStr;
    for (auto d : result) {
        resultStr += std::to_string(d);
    }
    
    return Octal(resultStr);
}

// Умножение
Octal Octal::multiply(const Octal& other) const {
    if (isZero() || other.isZero()) {
        return Octal();
    }
    
    size_t resultSize = digits.size() + other.digits.size();
    std::vector<unsigned char> result(resultSize, 0);
    
    // Умножаем как в столбик (цифры хранятся в обратном порядке для удобства)
    std::vector<unsigned char> revDigits1, revDigits2;
    for (size_t i = 0; i < digits.size(); ++i) {
        revDigits1.push_back(digitAt(i));
    }
    for (size_t i = 0; i < other.digits.size(); ++i) {
        revDigits2.push_back(other.digitAt(i));
    }
    
    for (size_t i = 0; i < revDigits2.size(); ++i) {
        unsigned char carry = 0;
        for (size_t j = 0; j < revDigits1.size(); ++j) {
            size_t pos = i + j;
            unsigned char product = result[pos] + revDigits2[i] * revDigits1[j] + carry;
            result[pos] = product % 8;
            carry = product / 8;
        }
        
        if (carry > 0) {
            result[i + revDigits1.size()] += carry;
        }
    }
    
    // Удаляем ведущие нули
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    
    // Переворачиваем
    std::reverse(result.begin(), result.end());
    
    // Создаем строку
    std::string resultStr;
    for (auto d : result) {
        resultStr += std::to_string(d);
    }
    
    return Octal(resultStr);
}

// Сравнение: больше чем
bool Octal::isGreaterThan(const Octal& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() > other.digits.size();
    }
    
    for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] > other.digits[i];
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
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
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
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }
    
    return true;
}

// Преобразование в строку
std::string Octal::toString() const {
    std::string result;
    for (auto d : digits) {
        result += std::to_string(d);
    }
    return result;
}

// Размер числа (количество цифр)
size_t Octal::size() const noexcept {
    return digits.size();
}

// Проверка на ноль
bool Octal::isZero() const noexcept {
    return digits.size() == 1 && digits[0] == 0;
}

// Получение цифры по позиции (0 - младший разряд)
unsigned char Octal::digitAt(size_t position) const {
    if (position < digits.size()) {
        // Цифры хранятся в обычном порядке (старший разряд в начале)
        // Для доступа к младшему разряду нужен обратный порядок
        return digits[digits.size() - 1 - position];
    }
    return 0;
}