#include <iostream>

struct B {
    int x;
    int y;
};

struct A {
    long long y;
    int x;
    B b;
};  

int main() {
    A a;
    std::cout << sizeof(a) << '\n';
}