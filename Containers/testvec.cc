#include <cstddef>
#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class Vector {
    private:
        int capacity;
        int size;
        T* buffer;
    public:
        Vector() : capacity(0), size(0), buffer(nullptr) {}

        Vector(int sz) : capacity(sz), size(sz), buffer(new T[sz]) {}

        Vector(unsigned int sz, int initalValue) : capacity(sz), size(sz), buffer(new T[sz]) {
            for(size_t i = 0; i < sz; i++) 
                buffer[i] = initalValue;
        }

        Vector(const Vector<T>& other) : capacity(other.capacity), size(other.size), buffer(new T[other.size]) {
            for(size_t i = 0; i < size; i++) 
                buffer[i] = other.buffer[i];
        }

        Vector(Vector<T>&& other) {
            swap(*this, other);
        }

        Vector<T>& operator=(const Vector<T>& other) {
            Vector<T> cpy(other);
            swap(*this, cpy);
            return *this;
        }

        Vector<T>& operator=(Vector<T>&& other) {
            swap(*this, other);
            return *this;
        }

        ~Vector() {
            delete[] buffer;
        }

        friend void swap(Vector<T>& a, Vector<T>& b) {
            using std::swap;
            swap(a.size, b.size);
            swap(a.capacity, b.capacity);
            swap(a.buffer, b.buffer);
        }

        int getSize() {return size;}
        T& operator [](unsigned int idx) {return buffer[idx];}

        void push_back(int val) {
            if(size >= capacity) 
                reserve(capacity * 2);
            buffer[size++] = val;
        }

        void reserve(int new_capacity) {
            if(!buffer) {
                size=0;
                capacity = 0;
            }
            T* newBuffer = new T[new_capacity];
            int new_size = new_capacity < size ? new_capacity : size;
            for(int i = 0; i < new_size; i++) 
                newBuffer[i] = buffer[i];
            capacity = new_capacity;
            delete[] buffer;
            buffer=newBuffer;
        }

};


int main() {
    Vector<int> a(2);
    Vector<int> b(2,10);

    a = b;

    a.push_back(3);
    a.push_back(4);
    for(int i = 0; i < a.getSize(); i++)
        std::cout << a[i] << ' ';
    

}