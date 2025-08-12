#include <iostream>

template<typename T>
class vector{
private:
    T* _data;
    size_t _size;
    size_t _capacity;
    void realocate(size_t capacity);
public:
    vector();
    vector(size_t size);
    vector(vector& other);
    vector(vector&& other) noexcept;
    vector<T>& operator=(vector& other);
    vector<T>& operator=(vector&& other) noexcept;

    T& at(size_t index) const;
    const T& at(size_t index) const;
    vector<T>& operator[](size_t index) const;
    const vector<T>& operator[](size_t index) const;

};