#pragma once

#include "array.hpp"
#include <string>
#include <stdexcept>

namespace octal {
    class Octal {
    private:
        Array::Array digits;
        
        void removeLeadingZeros();
        void validateDigit(unsigned char digit) const;
        
    public:
        // Конструкторы
        Octal();
        Octal(const size_t& n, unsigned char t = 0);
        Octal(const std::initializer_list<unsigned char>& t);
        Octal(const std::string& t);
        
        // Конструкторы копирования и перемещения
        Octal(const Octal& other);
        Octal(Octal&& other) noexcept;
        
        // Операторы присваивания (ДОБАВЛЯЕМ!)
        Octal& operator=(const Octal& other);
        Octal& operator=(Octal&& other) noexcept;
        
        // Деструктор
        ~Octal() noexcept;
        
        // Арифметические операции
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
        unsigned char digitAt(size_t position) const;
    };
}