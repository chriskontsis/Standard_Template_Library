#include <iostream>

using namespace std;
template<class T> 
class Vector {
private:
    unsigned int my_size;
    unsigned int my_capacity;
    T* buffer;
public:
    Vector() : my_size(0), my_capacity(0), buffer(0) {};
    Vector(unsigned int size): my_size(size), my_capacity(size), buffer(new T[size]) {};

    Vector(unsigned int size, const T& initial) : my_size(size), my_capacity(size), buffer(new T[size]) {
        for(auto i = 0; i < size; i++) 
            buffer[i] = initial;
    } 

    Vector(const Vector<T> & v) : my_size(v.my_size), my_capacity(v.my_capacity), buffer(new T[v.my_size]) {
        for(auto i = 0; i < size; i++) 
            buffer[i] = v.buffer[i];
    }
    ~Vector() {
        delete[] buffer;
    }

    unsigned int capatity() const {
        return my_capacity;
    }

    unsigned int size() const {
        return my_size;
    }

    bool empty() const {};

    T* begin() {
        return buffer;
    }
    T* end() {
        return buffer + my_size;
    }

    T& front() {
        return buffer[0];
    }
    T& back() {
        return buffer[my_size -1];
    }

    void push_back(const T& value) {

    }
    
    void pop_back();
    void reserve(unsigned int capacity);
    void resize (unsigned int size);

    T& operator[](unsigned int index);
    Vector<T> & operator=(const Vector<T>& vec);
    void clear();
};

int main() {
    Vector<int> vec(10,1);

}

