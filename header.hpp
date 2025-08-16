#pragma once
#include <utility>
#include <initializer_list>
#include <iostream>

template<typename T>
class vector {
private:
    T* _data;
    size_t _size;
    size_t _capacity;
    void reallocate(size_t capacity);

public:
    vector();
    explicit vector(size_t size);
    explicit vector(const vector& other);
    explicit vector(vector&& other) noexcept;
    vector<T>& operator=(const vector& other);
    vector<T>& operator=(vector&& other) noexcept;
    ~vector();

    //ellement access
    T& at(size_t index);
    const T& at(size_t index) const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& first();
    const T& first() const;
    T& last();
    const T& last() const;
    T* data();
    const T* data() const;

    //Capacity
    bool empty() const noexcept;
    size_t size() const noexcept;
    //size_t max_size() const noexcept;
    void reserve(size_t capacity);
    size_t capacity() const noexcept;
    void shrink_to_fit();

    //Modifiers
    void clear() noexcept;
    void insert(const size_t pos, const T& value);
    void insert(const size_t pos, T&& value);
    void insert(const size_t pos,const size_t count, const T& value);
    void insert(const size_t pos, std::initializer_list<T> ilist);
    template< class... Args >
    void emplace(const size_t pos, Args&&... args);
    void erase(const size_t pos);
    void erase(const size_t first, const size_t last);
    void push_back(const T& value);
    void push_back( T&& value );
    template< class... Args >
    void emplace_back( Args&&... args );
    void pop_back();
    void resize(size_t count);
    void resize( size_t count, const T& value );
    
    //Non-member
    template<typename U>
    friend bool operator==(const vector<U>& lhs, const vector<U>& rhs);
    
    template<typename U>
    friend bool operator!=(const vector<U>& lhs, const vector<U>& rhs);

    template<typename U>
    friend bool operator<(const vector<U>& lhs, const vector<U>& rhs);

    template<typename U>
    friend bool operator<=(const vector<U>& lhs, const vector<U>& rhs);

    template<typename U>
    friend bool operator>(const vector<U>& lhs, const vector<U>& rhs);

    template<typename U>
    friend bool operator>=(const vector<U>& lhs, const vector<U>& rhs);

    
    //Output
    void print() const;
};

#include "source.tpp"
