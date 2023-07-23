#include <iostream>


template<typename T>
class Vector {
    private:
        int size;
        int capacity;
        T* data_;

    public:
        Vector() : size(0), capacity(0), data_(nullptr) {}

        Vector(unsigned int new_size) : size(new_size), capacity(new_size), data_(new T[new_size]) {}

        ~Vector() {
            delete[] data_;
        }

        void Push_Back(T val) {
            if(size >= capacity)  {
                size_t new_capacity = capacity == 0 ? 1 : 2 * capacity;
                T* new_data = new T[new_capacity];
                for(size_t i = 0; i < size; i++) 
                    new_data[i] = data_[i];
                delete[] data_;
                data_ = new_data;
                capacity=new_capacity;
            }
            data_[size++] = val;

        }

        T& operator[](int idx) {return data_[idx];}

        int get_size() {return size;}
        int get_capacity() {return capacity;}


};


int main() {
    Vector<int> v;
    v.Push_Back(1);
    std::cout << v.get_size() << ' ' << v.get_capacity() << '\n';
    v.Push_Back(2);
    v.Push_Back(3);

}