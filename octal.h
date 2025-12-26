#pragma once

#include <cstddef>
#include <string>
#include <initializer_list>
#include <stdexcept>
#include <vector>

class Octal {
private:
    std::vector<unsigned char> digits;  // Цифры (0-7), старший разряд в начале
    
    void removeLeadingZeros();
    void validateDigit(unsigned char digit) const;
    
public:
    // Конструкторы
    Octal();
    Octal(size_t n, unsigned char t = 0);
    Octal(const std::initializer_list<unsigned char>& t);
    Octal(const std::string& t);
    
    // Конструкторы копирования и перемещения
    Octal(const Octal& other) = default;
    Octal(Octal&& other) noexcept = default;
    
    // Операторы присваивания
    Octal& operator=(const Octal& other) = default;
    Octal& operator=(Octal&& other) noexcept = default;
    
    // Деструктор
    ~Octal() = default;
    
    // Арифметические операции (методы класса)
    Octal add(const Octal& other) const;
    Octal subtract(const Octal& other) const;
    Octal multiply(const Octal& other) const;
    
    // Операции сравнения
    bool isGreaterThan(const Octal& other) const;
    bool isLessThan(const Octal& other) const;
    bool isEqual(const Octal& other) const;
    
    // Вспомогательные методы
    std::string toString() const;
    size_t size() const noexcept;
    bool isZero() const noexcept;
    unsigned char digitAt(size_t position) const;  // position=0 - младший разряд
    
    // Для тестирования и отладки
    const std::vector<unsigned char>& getDigits() const { return digits; }
};