//Modifiers
#include <utility>
#include "header.hpp"
template<typename T>
void vector<T>::reallocate(size_t capacity) {
    T* tmp = new T[capacity];
    for (size_t i = 0; i < _size; i++) {
        tmp[i] = std::move(_data[i]);
    }
    delete[] _data;
    _data = tmp;
    _capacity = capacity;
}

template<typename T>
vector<T>::vector() : _data(nullptr), _size(0), _capacity(0) {}

template<typename T>
vector<T>::vector(size_t size) : _data(new T[size]), _size(size), _capacity(size) {};

template<typename T>
vector<T>::vector(size_t count, const T& value) : vector(count){
    for (size_t i = 0; i < count; i++) {
        _data[i] = value;
    }
}


template<typename T>
vector<T>::vector(const vector& other) : _size(other._size), _capacity(other._capacity) {
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

template<typename T>
vector<T>::vector(vector&& other) noexcept
    : _data(other._data), _size(other._size), _capacity(other._capacity) {
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template<typename T>
vector<T>& vector<T>::operator=(const vector& other) {
    if (this == &other) return *this;

    delete[] _data;
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
    return *this;
}

template<typename T>
vector<T>& vector<T>::operator=(vector&& other) noexcept {
    if (this == &other) return *this;

    delete[] _data;
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    return *this;
}

template<typename T>
vector<T>::~vector() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}


//ellement access
template<typename T>
T& vector<T>::at(size_t index) {
    if (index >= _size) throw std::out_of_range("Index out of range");
    return _data[index];
}

template<typename T>
const T& vector<T>::at(size_t index) const {
    if (index >= _size) throw std::out_of_range("Index out of range");
    return _data[index];
}

template<typename T>
T& vector<T>::operator[](size_t index) {
    return _data[index];
}

template<typename T>
const T& vector<T>::operator[](size_t index) const {
    return _data[index];
}

template<typename T>
T& vector<T>::first() { 
    if (_size > 0) return _data[0];
    else throw std::out_of_range("index out of range");
}

template<typename T>
const T& vector<T>::first() const { 
    if (_size > 0) return _data[0];
    else throw std::out_of_range("index out of range");
}

template<typename T>
T& vector<T>::last() { 
    if (_size > 0) return _data[_size - 1];
    else throw std::out_of_range("index out of range");
}

template<typename T>
const T& vector<T>::last() const {
    if (_size > 0) return _data[_size - 1];
    else throw std::out_of_range("index out of range");
}

template<typename T>
T* vector<T>::data() noexcept { return _data; }

template<typename T>
const T* vector<T>::data() const noexcept { return _data; }


//size
template<typename T>
bool vector<T>::empty() const noexcept { return _size == 0; }

template<typename T>
size_t vector<T>::size() const noexcept { return _size; }

template<typename T>
void vector<T>::reserve(size_t capacity) {
    if (capacity > _capacity) {
        reallocate(capacity);
    }
}

template<typename T>
size_t vector<T>::capacity() const noexcept { return _capacity; }

template<typename T>
void vector<T>::shrink_to_fit() { reallocate(_size); }

//Modifiers
template<typename T>
void vector<T>::clear() noexcept {
    for (size_t i = 0; i < _size; i++) {
        _data[i].~T();
    }
    _size = 0;
}

template<typename T>
void vector<T>::insert(const size_t pos, const T& value) {
    if (pos > _size) return;
    if (_size + 1 >= _capacity) { reallocate(_capacity == 0 ? 1 : _capacity * 2); }

    for (size_t i = _size; i > pos; i--) {
        _data[i] = _data[i-1];
    }
    _data[pos] = value;
}

template<typename T>
void vector<T>::insert( const size_t pos, T&& value ) {
    if (pos > _size) return;
    if (_size + 1 >= _capacity) { reallocate(_capacity == 0 ? 1 : _capacity * 2); }

    for (size_t i = _size; i > pos; i--) {
        _data[i] = std::move(_data[i-1]);
    }
    _data[pos] = std::move(value);
}

template<typename T>
void vector<T>::insert(const size_t pos,const size_t count, const T& value) {
    for (size_t i = 0; i < count; i++) {
        insert(pos, value);
    }
}

template<typename T>
void vector<T>::insert(const size_t pos, std::initializer_list<T> ilist) {
    size_t n = pos;
    for (const auto& i : ilist) {
        insert(n, i);
        n++;
    }
}

template<typename T>
template< class... Args >
void vector<T>::emplace(const size_t pos, Args&&... args) {
    if (pos > _size) return;
    if (_size + 1 >= _capacity) { reallocate(_capacity == 0 ? 1 : _capacity * 2); }


    for (size_t i = _size; i > pos; i--) {
        _data[i] = std::move(_data[i-1]);
    }

    new(&_data[pos]) T(std::forward<Args>(args)...);
}

template<typename T>
void vector<T>::erase(const size_t pos) {
    if (pos > _size) return;
    if (_size == _capacity) reallocate(_size * 2);
    for (size_t i = pos; i <= _size; i++) {
        _data[i] = std::move(_data[i+1]);
    }
    _data[--_size].~T();
}

template<typename T>
void vector<T>::erase(const size_t first, const size_t last) {
    for (size_t i = first; i <= last; i++) {
        erase(first);
    }
}

template<typename T>
void vector<T>::push_back(const T& value) {
    if (_size + 1 >= _capacity) { reallocate(_capacity == 0 ? 1 : _capacity * 2); }
    _data[_size-1] = value;
}

template<typename T>
void vector<T>::push_back(T&& value) {
    if (_size + 1 >= _capacity) { reallocate(_capacity == 0 ? 1 : _capacity * 2); }
    _data[_size-1] = std::move(value);
}

template<typename T>
template<class... Args >
void vector<T>::emplace_back( Args&&... args ) {
    if (_size + 1 >= _capacity) { reallocate(_capacity == 0 ? 1 : _capacity * 2); }
    new(&_data[_size-1]) T(std::forward<Args>(args)...);
}

template<typename T>
void vector<T>::pop_back() {
    if(_size == 0) return;
    _data[--_size].~T();
}

template<typename T>
void vector<T>::resize(size_t count) {
    if (count > _capacity) { reallocate(count * 2); }
    if (count > _size) {
        while (_size < count) {
            new(&_data[_size++]) T(0);
        }
    }
    else if(count < _size) {
        while (_size > count) {
            _data[--_size].~T();
        }
    }
}

template<typename T>
void vector<T>::resize(size_t count, const T& value) {
    if (count > _capacity) { reallocate(count * 2); }
    if (count > _size) {
        while (_size < count) {
            new(&_data[_size++]) T(value);
        }
    }
    else if(count < _size) {
        while (_size > count) {
            _data[--_size].~T();
        }
    }
}

template<typename T>
void vector<T>::swap(vector& other) {
    std::swap(_data, other._data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
}

template<typename U>
bool operator==(const vector<U>& lhs, const vector<U>& rhs) {
    if (lhs._size != rhs._size) return false;
    for (size_t i = 0; i < lhs._size; i++) {
        if (lhs._data[i] != rhs._data[i]) return false;
    }
    return true;
}

template<typename U>
bool operator!=(const vector<U>& lhs, const vector<U>& rhs) {
    return !(lhs == rhs);
}


template<typename U>
bool operator>(const vector<U>& lhs, const vector<U>& rhs) {
    size_t min_size = lhs._size > rhs._size ? lhs._size : rhs._size;
    for (size_t i = 0; i < min_size; i++) {
        if (lhs[i] > rhs[i]) return true;
        if (lhs[i] < rhs[i]) return false;
    }
    return lhs._size > rhs._size;
}

template<typename U>
bool operator>=(const vector<U>& lhs, const vector<U>& rhs) {
    return !(lhs > rhs);
}

template<typename U>
bool operator<(const vector<U>& lhs, const vector<U>& rhs) {
    return rhs > lhs;
}

template<typename U>
bool operator<=(const vector<U>& lhs, const vector<U>& rhs) {
    return !(rhs > lhs);
}

//Output
template<typename T>
void vector<T>::print() const {
    for (size_t i = 0; i < _size; i++) {
        std::cout << _data[i] << ' ';
    }
    std::cout << std::endl;
}

