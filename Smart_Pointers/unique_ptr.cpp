// template <class T>
// class UniquePtr {
// private:
//     T* _ptr = nullptr;
// public:
//     UniquePtr() : _ptr(nullptr) {}
//     explicit UniquePtr(T* ptr = nullptr):_ptr(ptr){}
//     // move only type so copy constructor is deleted
//     UniquePtr(const UniquePtr& ptr) = delete;
//     // move constructor, releasees whatever other was pointing to and 
//     // sets _ptr to that new object
//     UniquePtr(UniquePtr&& other) : _ptr(other.release()) {}
    

//     // Case Where you have a Base class pointer pointing to a derived class. 
//     template<class U>
//     UniquePtr(UniquePtr<U>&& other) : _ptr(other.release()) {}
    
//     ~UniquePtr () {
//         reset();
//     }

//     // copy constructor not allowed;
//     UniquePtr& operator=(const UniquePtr& other) = delete;

//     /*
//     release on other sets other pointing to nullptr and returns what
//     other was pointing to. Then reset is called with the other's object
//     which then releases the current _ptr of the class and sets _ptr to whatever
//     other was pointing tp and then finally deletes the object _ptr was 
//     previosuly pointing to. 
//     */    
//     UniquePtr& operator=(UniquePtr&& other) {
//         reset(other.release());
//         return *this;
//     }
//     template<class U>
//     UniquePtr& operator=(UniquePtr<U>&& other) {
//         reset(other.release());
//         return *this;
//     }

//     T* get() const {return _ptr;}

//     T* operator->() const {return get()};

//     T& operator*() const {return *get()};


//     T* release() {
//         auto oldptr = _ptr;
//         _ptr = nullptr;
//         return oldptr;
//     }

//     void reset(T* newPtr = nullptr) {
//         auto oldPtr = release();
//         _ptr = newPtr;
//         if(oldPtr != nullptr) {
//             delete oldPtr;
//         }
//     }

//     void swap(UniquePtr& other) {
//         std::swap(this->_ptr, other._ptr);
//     }

//     explicit operator bool() {
//         return get() != nullptr;
//     }
// };

// int main() {

// }

    template<typename T>
    class UP
    {
        T*   data;
        public:
            UP()
                : data(nullptr)
            {}
            // Explicit constructor
            explicit UP(T* data)
                : data(data)
            {}
            ~UP()
            {
                delete data;
            }

            // Constructor/Assignment that binds to nullptr
            // This makes usage with nullptr cleaner
            UP(std::nullptr_t)
                : data(nullptr)
            {}
            UP& operator=(std::nullptr_t)
            {
                reset();
                return *this;
            }

            // Constructor/Assignment that allows move semantics
            UP(UP&& moving) noexcept
                : data(nullptr)
            {
                moving.swap(*this);
                // In the comments it was pointed out that this
                // does not match the implementation of std::unique_ptr
                // I am going to leave mine the same. But
                // the the standard provides some extra guarantees
                // and probably a more intuitive usage.
            }
            UP& operator=(UP&& moving) noexcept
            {
                moving.swap(*this);
                return *this;
                // See move constructor.
            }

            // Constructor/Assignment for use with types derived from T
            template<typename U>
            UP(UP<U>&& moving)
            {
                UP<T>   tmp(moving.release());
                tmp.swap(*this);
            }
            template<typename U>
            UP& operator=(UP<U>&& moving)
            {
                UP<T>    tmp(moving.release());
                tmp.swap(*this);
                return *this;
            }

            // Remove compiler generated copy semantics.
            UP(UP const&)            = delete;
            UP& operator=(UP const&) = delete;

            // Const correct access owned object
            T* operator->() const {return data;}
            T& operator*()  const {return *data;}

            // Access to smart pointer state
            T* get()                 const {return data;}
            explicit operator bool() const {return data;}

            // Modify object state
            T* release() noexcept
            {
                T* result = nullptr;
                std::swap(result, data);
                return result;
            }
            void swap(UP& src) noexcept
            {
                std::swap(data, src.data);
            }
            void reset()
            {
                T* tmp = release();
                delete tmp;
            }
    };
    template<typename T>
    void swap(UP<T>& lhs, UP<T>& rhs)
    {
        lhs.swap(rhs);
    }