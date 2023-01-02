
#include <memory>
#include <iostream> 

#define endl '\n';

template<typename T>
class SP
{
private:
    T* ptr;
    unsigned int* refcount;
public:

    SP() : ptr(nullptr), refcount(nullptr) {};
    explicit SP(T* _ptr) : ptr(_ptr), refcount(new unsigned int(1)) {};
    
    ~SP() {
        --(*refcount);
        if(!(*refcount)) {
            delete ptr;
            delete refcount;
        }
    }
    //copy constructor
    SP(const SP& copy) : ptr(copy.ptr), refcount(copy.refcount)
    {
        ++(*refcount);
    }
    // copy assignment
    SP& operator=(const SP& copy) {
        if(this != &copy) {
            reset();
            ptr = copy.ptr;
            refcount = copy.refcount;
            ++(*refcount);
        }
        return *this;
    }
    // copy from derived;
    template<typename U>
    SP& operator=(const SP<U>& rhs) {
        if(this != &rhs) {
            reset();
            ptr = rhs.ptr;
            refcount=rhs.refcount;
            ++(*refcount);
        }
        return *this;
    }


    SP(SP&& moving) noexcept : ptr(moving.ptr), refcount(moving.refcount) {
        moving.refcount = nullptr;
        moving.ptr = nullptr;
    }
    SP& operator=(SP&& moving) {
        if(this != &moving) {
            reset();
            ptr = moving.ptr;
            refcount = moving.refcount;
            moving.ptr = nullptr;
            moving.refcount = nullptr;
        }
        return *this;
    }

    T& operator*() const {return *ptr;}
    T* operator->() const {return ptr;}
    operator bool() const noexcept {return ptr != nullptr;}

    T* get() const noexcept {return ptr;}
    unsigned int& use_count() const noexcept {return *refcount;}

    void reset() {
        if(*refcount) {
            if(--(*refcount) == 0) {
                delete ptr;
                delete refcount;
            }
        }
        ptr = nullptr;
        refcount = nullptr;
    }

    friend void swap(SP& lhs, SP& rhs) noexcept {
        using std::swap;
        swap(lhs.ptr, rhs.ptr);
        swap(lhs.refcount, rhs.refcount);
    }

};



using namespace std;
int main() {
    SP<int> sp(new int(2));
    shared_ptr<int> asp(new int(2));
    cout << "Checking parameter constructor " << endl;
    cout << "------------------------------" << endl;
    cout << asp.use_count() << endl;
    cout << sp.use_count() << endl;

    shared_ptr<int> asp2 = asp;
    SP<int> sp2 = sp;

    cout << "Checking copy constructor " << endl;
    cout << "--------------------------" << endl;
    cout << asp2.use_count() << endl;
    cout << sp2.use_count() << endl;

    asp2 = asp2;
    sp2 = sp2;

    cout << "Checking self assignment " << endl;
    cout << "-------------------------" << endl;
    cout << asp2.use_count() << endl;
    cout << sp2.use_count() << endl;

    cout << "Checking copy decrement works " << endl;
    cout << "-----------------------------" << endl;
    SP<int> nsp1(new int(1));
    SP<int> nsp2 = nsp1;
    cout << "Before reassignment" << endl;
    cout << "nsp2 ref count " << '\n';
    cout << nsp2.use_count() << '\n';
    SP<int> nsp3(new int(4));
    nsp1 = nsp3;
    cout << "After reassigning nsp1 nsp2 use count is " << endl;
    cout << nsp2.use_count() << endl;

}   