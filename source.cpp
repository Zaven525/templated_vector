#include "header.hpp"
template<typename T>
void vector<T>::realocate(size_t capacity) {
    T* tmp = new T[capacity];
    for (size_t i = 0; i < _size; i++) {
        tmp[i] = std::move(_data[i]);
    }
    delete [] _data;
    _data = tmp;
    _capacity = capacity;
}

template<typename T>
vector<T>::vector() : _data{nullptr}, _size{0}, _capacity{0} {}

template<typename T>
vector<T>::vector(size_t size) : _data{new T[size]}, _size{size}, _capacity{size} {}

template<typename T>
vector<T>::vector(vector& other) : _size{other._size}, _capacity{other._capacity}{
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

template<typename T>
vector<T>::vector(vector&& other) noexcept : _size{other._size}, _capacity{other._capacity}, _data{other._data}{
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template<typename T>
vector<T>& vector<T>::operator=(vector& other) {
    if (&other == this) {
        return *this;
    }

    _data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
    return *this;
}

template<typename T>
vector<T>& vector<T>::operator=(vector&& other) noexcept {
    if (&other == this) {
        return *this;
    }
    delete [] _data;
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    return *this;
}

template<typename T>
T& vector<T>::at(size_t index) const{
    return _data[index];
}

template<typename T>
const T& vector<T>::at(size_t index) const {
    return _data[index];
}
template<typename T>
vector<T>& vector<T>::operator[](size_t index) const {
    return _data[index];
}

template<typename T>
const vector<T>& vector<T>::operator[](size_t index) const {
    return _data[index];
}