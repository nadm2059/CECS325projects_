// Author: Nadhirah Michael-Ho
// CECS 325-02 Prog X
// Project Name(Prog X - Gold Namespace)
// Due 05/01/2025
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program

// goldNamespace.cpp
#ifndef GOLD_NAMESPACE_CPP
#define GOLD_NAMESPACE_CPP

#include <stdexcept>
#include <iostream>

namespace gold {
    template <typename T>
    class vector {
    private:
        T* data;
        int _size;
        int _capacity;

        void resize(int new_capacity) {
            if (new_capacity <= _capacity) return;
            T* new_data = new T[new_capacity];
            for (int i = 0; i < _size; i++)
                new_data[i] = data[i];
            delete[] data;
            data = new_data;
            _capacity = new_capacity;
        }

    public:
        // Constructors
        vector() : data(nullptr), _size(0), _capacity(0) {}

        vector(int n) : _size(n), _capacity(n) {
            data = new T[_capacity]();
        }

        vector(int n, T val) : _size(n), _capacity(n) {
            data = new T[_capacity];
            for (int i = 0; i < n; ++i)
                data[i] = val;
        }

        // Destructor
        ~vector() {
            delete[] data;
        }

        // Copy constructor
        vector(const vector& other) {
            _size = other._size;
            _capacity = other._capacity;
            data = new T[_capacity];
            for (int i = 0; i < _size; i++)
                data[i] = other.data[i];
        }

        // Assignment operator
        vector& operator=(const vector& other) {
            if (this == &other)
                return *this;
            delete[] data;
            _size = other._size;
            _capacity = other._capacity;
            data = new T[_capacity];
            for (int i = 0; i < _size; i++)
                data[i] = other.data[i];
            return *this;
        }

        // Element access
        T& operator[](int index) {
            return data[index];
        }

        T& at(int index) {
            if (index < 0 || index >= _size)
                throw "Index out of bounds!";
            return data[index];
        }


        T& front() {
            return data[0];
        }

        T& back() {
            return data[_size - 1];
        }

        // Capacity
        int size() const {
            return _size;
        }

        int capacity() const {
            return _capacity;
        }

        bool empty() const {
            return _size == 0;
        }

        // Modifiers
        void push_back(const T& val) {
            if (_size == _capacity)
                resize(_capacity == 0 ? 1 : _capacity * 2);
            data[_size++] = val;
        }

        void pop_back() {
            if (_size > 0)
                --_size;
        }

        void clear() {
            _size = 0;
        }
    };
}

#endif
