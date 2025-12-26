#include "array.hpp"
#include <algorithm>
#include <cstring>
#include <stdexcept>

namespace Array {
    // Конструктор по умолчанию
    Array::Array() : _size(0), _data(nullptr) {}
    
    // Конструктор с размером и значением
    Array::Array(const size_t& n, unsigned char value) : _size(n) {
        if (n > 0) {
            try {
                _data = new unsigned char[n];
                for (size_t i = 0; i < n; ++i) {
                    _data[i] = value;
                }
            } catch (const std::bad_alloc& e) {
                _size = 0;
                _data = nullptr;
                throw;
            }
        } else {
            _data = nullptr;
        }
    }
    
    // Конструктор со списком инициализации
    Array::Array(const std::initializer_list<unsigned char>& list) : _size(list.size()) {
        if (_size > 0) {
            try {
                _data = new unsigned char[_size];
                size_t i = 0;
                for (const unsigned char& value : list) {
                    _data[i++] = value;
                }
            } catch (const std::bad_alloc& e) {
                _size = 0;
                _data = nullptr;
                throw;
            }
        } else {
            _data = nullptr;
        }
    }
    
    // Конструктор из строки
    Array::Array(const std::string& str) : _size(str.size()) {
        if (_size > 0) {
            try {
                _data = new unsigned char[_size];
                for (size_t i = 0; i < _size; ++i) {
                    _data[i] = static_cast<unsigned char>(str[i]);
                }
            } catch (const std::bad_alloc& e) {
                _size = 0;
                _data = nullptr;
                throw;
            }
        } else {
            _data = nullptr;
        }
    }
    
    // Конструктор копирования
    Array::Array(const Array& other) : _size(other._size) {
        if (_size > 0 && other._data != nullptr) {
            try {
                _data = new unsigned char[_size];
                for (size_t i = 0; i < _size; ++i) {
                    _data[i] = other._data[i];
                }
            } catch (const std::bad_alloc& e) {
                _size = 0;
                _data = nullptr;
                throw;
            }
        } else {
            _data = nullptr;
        }
    }
    
    // Конструктор перемещения
    Array::Array(Array&& other) noexcept 
        : _size(other._size), _data(other._data) {
        other._size = 0;
        other._data = nullptr;
    }
    
    // Деструктор
    Array::~Array() noexcept {
        delete[] _data;
    }
    
    // Оператор присваивания копированием
    Array& Array::operator=(const Array& other) {
        if (this != &other) {
            // Создаем временную копию
            Array temp(other);
            
            // Обмениваем содержимое с помощью swap
            std::swap(_size, temp._size);
            std::swap(_data, temp._data);
        }
        return *this;
    }
    
    // Оператор присваивания перемещением
    Array& Array::operator=(Array&& other) noexcept {
        if (this != &other) {
            // Освобождаем текущие ресурсы
            delete[] _data;
            
            // Перемещаем ресурсы из other
            _size = other._size;
            _data = other._data;
            
            // Обнуляем other
            other._size = 0;
            other._data = nullptr;
        }
        return *this;
    }
    
    // Получение размера
    size_t Array::size() const noexcept {
        return _size;
    }
    
    // Проверка на пустоту
    bool Array::isEmpty() const noexcept {
        return _size == 0;
    }
    
    // Доступ к элементу с проверкой границ
    unsigned char Array::at(size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }
    
    // Получение указателя на данные
    const unsigned char* Array::data() const noexcept {
        return _data;
    }
    
    // Получение элемента по индексу (ссылка)
    const unsigned char& Array::getByIndex(size_t pos) const {
        if (pos >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[pos];
    }
    
    // Первый элемент
    const unsigned char& Array::front() const {
        if (_size == 0) {
            throw std::out_of_range("Array is empty");
        }
        return _data[0];
    }
    
    // Последний элемент
    const unsigned char& Array::back() const {
        if (_size == 0) {
            throw std::out_of_range("Array is empty");
        }
        return _data[_size - 1];
    }
}