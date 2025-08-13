#include <utility>

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
vector<T>::vector(size_t size) : _data(new T[size]), _size(size), _capacity(size) {}

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
    if (index >= _size) throw std::out_of_range("Index out of range");
    return _data[index];
}

template<typename T>
const T& vector<T>::operator[](size_t index) const {
    if (index >= _size) throw std::out_of_range("Index out of range");
    return _data[index];
}

template<typename T>
T& vector<T>::first() { return _size > 0 ? _data[0] : nullptr; }

template<typename T>
const T& vector<T>::first() const { return _size > 0 ? _data[0] : nullptr; }

template<typename T>
T& vector<T>::last() { return _size > 0 ? _data[_size - 1] : nullptr; }

template<typename T>
const T& vector<T>::last() const {return _size > 0 ? _data[_size - 1] : nullptr; }

template<typename T>
T* vector<T>::data() { return _data; }

template<typename T>
const T* vector<T>::data() const { return _data; }


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
    _size++;
    if (_size > _capacity) { reallocate(_size * 2); }

    for (size_t i = _size; i > pos; i--) {
        _data[i] = _data[i-1];
    }
    _data[pos] = value;
}

template<typename T>
void vector<T>::insert( const size_t pos, T&& value ) {
    if (pos > _size) return;
    _size++;
    if (_size > _capacity) { reallocate(_size * 2); }

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
    _size++;
    if (_size > _capacity) { reallocate(_size * 2); }

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
    _size++;
    if (_size >= _capacity) reallocate(_size * 2);
    _data[_size-1] = value;
}

template<typename T>
void vector<T>::push_back(T&& value) {
    _size++;
    if (_size >= _capacity) reallocate(_size * 2);
    _data[_size-1] = std::move(value);
}

template<typename T>
template<class... Args >
void vector<T>::emplace_back( Args&&... args ) {
    _size++;
    if(_size >= _capacity) reallocate(_size * 2);
    new(&_data[_size-1]) T(std::forward<Args>(args)...);
}

template<typename T>
void vector<T>::pop_back() {
    if(_size == 0) return;
    _data[--_size].~T();
}

//Output
template<typename T>
void vector<T>::print() const {
    for (size_t i = 0; i < _size; i++) {
        std::cout << _data[i] << ' ';
    }
    std::cout << std::endl;
}

