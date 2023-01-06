using namespace std;


template<class T> 
class Vector {
private:
    unsigned int my_size;
    unsigned int my_capacity;
    T* buffer;
public:
    Vector();
    Vector(unsigned int size);
    Vector(unsigned int size, const T& inital);
    Vector(const Vector<T> & v);
    ~Vector();

    unsigned int capatity() const;
    unsigned int size() const;
    bool empty() const;
    T* begin();
    T* end();
    T& front();
    T& back();
    void push_back(const T& value);
    void pop_back();
    void reserve(unsigned int capacity);
    void resize (unsigned int size);

    T& operator[](unsigned int index);
    Vector<T> & operator=(const Vector<T>& vec);
    void clear();
};

