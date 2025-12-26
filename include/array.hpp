#pragma once

#include <cstddef>
#include <string>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>  // добавлено

namespace Array {
    class Array {
    private:
        size_t _size = 0;
        unsigned char* _data = nullptr;
        
    public:
        // Конструкторы
        Array();
        Array(const size_t& n, unsigned char t = 0);
        Array(const std::initializer_list<unsigned char>& t);
        Array(const std::string& t);
        
        // Конструкторы копирования и перемещения
        Array(const Array& other);
        Array(Array&& other) noexcept;
        
        // Операторы присваивания (ДОБАВЛЯЕМ!)
        Array& operator=(const Array& other);
        Array& operator=(Array&& other) noexcept;
        
        // Деструктор
        virtual ~Array() noexcept;
        
        // Методы доступа
        size_t size() const noexcept;
        bool isEmpty() const noexcept;
        unsigned char at(size_t index) const;
        
        // Метод получения данных
        const unsigned char* data() const noexcept;
        
        // Методы из образца
        const unsigned char& getByIndex(size_t pos) const;
        const unsigned char& front() const;
        const unsigned char& back() const;
    };
}