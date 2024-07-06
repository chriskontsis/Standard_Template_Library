#include <atomic>

template<typename T>
class SharedPtr 
{
    public:

        SharedPtr() noexcept = default;

        SharedPtr(std::nullptr_t) noexcept 
        {}

        // takes raw point of type T
        SharedPtr(T* p) 
        : ptr(p)
        , ref_count(new std::atomic<int>{1})

        // wrap raw pointer of convertible type from U to T
        template<typename U>
        SharedPtr(U* p) 
        {}

        // Copy Constructor
        SharedPtr(const SharedPtr& sp)
        : ptr(sp.ptr)
        , ref_count(sp.ref_count) 
        {
            if(sp)
                ++(*ref_count);
        }

        ~SharedPtr()
        {
            if(ptr) {
                if(--(*ref_count) == 0) {
                    delete ref_count;
                    delete ptr;
                }
            }
        }



    private:
        T* ptr;
        std::atomic<int>* ref_count;
};