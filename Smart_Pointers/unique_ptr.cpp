template <class T>
class UniquePtr {
private:
    T* _ptr = nullptr;
public:
    UniquePtr() : _ptr(nullptr) {}
    explicit UniquePtr(T* ptr = nullptr):_ptr(ptr){}
    // move only type so copy constructor is deleted
    UniquePtr(const UniquePtr& ptr) = delete;
    // move constructor, releasees whatever other was pointing to and 
    // sets _ptr to that new object
    UniquePtr(UniquePtr&& other) : _ptr(other.release()) {}
    
    template<class U>
    UniquePtr(UniquePtr<U>&& other) : _ptr(other.release()) {}
    ~UniquePtr () {
        reset();
    }

    // copy constructor not allowed;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    /*
    release on other sets other pointing to nullptr and returns what
    other was pointing to. Then reset is called with the other's object
    which then releases the current _ptr of the class and sets _ptr to whatever
    other was pointing tp and then finally deletes the object _ptr was 
    previosuly pointing to. 
    */    
    UniquePtr& operator=(UniquePtr&& other) {
        reset(other.release());
        return *this;
    }
    template<class U>
    UniquePtr& operator=(UniquePtr<U>&& other) {
        reset(other.release());
        return *this;
    }

    T* get() const {return _ptr;}

    T* operator->() const {return get()};

    T& operator*() const {return *get()};


    T* release() {
        auto oldptr = _ptr;
        _ptr = nullptr;
        return oldptr;
    }

    void reset(T* newPtr = nullptr) {
        auto oldPtr = release();
        _ptr = newPtr;
        if(oldPtr != nullptr) {
            delete oldPtr;
        }
    }

    void swap(UniquePtr& other) {
        std::swap(this->_ptr, other._ptr);
    }

    explicit operator bool() {
        return get() != nullptr;
    }
};

int main() {

}