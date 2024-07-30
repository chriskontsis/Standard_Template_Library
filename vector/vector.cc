#include <iostream>
#include <exception>


template<typename T>
class Vector {
    public:
        Vector() 
        : data (new T[1]), size(0), capacity(1)  
        { }


        Vector(const Vector& other)
        : data (new T[other.capacity]), size(other.size), capacity(other.capacity)
        { }

        Vector(Vector&& other)
        : data(other.data), size(other.size), capacity(other.capacity)
        {
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }

        Vector& operator=(Vector other)
        {
            if(this != &other)
                swap(*this, other);
            return *this;
        }


        ~Vector() 
        {
            delete[] data;
        }

        void push_back(T value) 
        {
            if(size == capacity)
                realloc(capacity * 2);
            data[size++] = value;
        }

        void pop_back()
        {
            if(size > 0)
                --size;
            else
                throw std::out_of_range("Empty vector");
        }

        void resize(size_t newSize)
        {
            if(newSize > capacity)
                realloc(newSize);
            size = newSize;
        }

        size_t getSize() const 
        {
            return size;
        }

        T& operator[](size_t idx) 
        {
            if(idx < 0 || idx >= size)
                throw std::out_of_range("Index out of bounds");
            return data[idx];
        }

        friend void swap(Vector& a, Vector& b)
        {
            using std::swap;
            swap(a.data, b.data);
            swap(a.capacity, b.capacity);
            swap(a.size, b.size);
        }


    private:
        void realloc(size_t newCapacity) 
        {
            T* newData = new T[newCapacity];
            for(size_t i = 0; i < size; ++i)
                newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

    private:
        T* data;
        size_t size;
        size_t capacity;
};

int main() {
    // Vector()
    Vector<int> vec;

    //push_back()
    vec.push_back(1);
    vec.push_back(2);
    std::cout << vec[1] << '\n';


    Vector<int> vec2;
    vec2 = vec;

}