#include <iostream>

typedef long long u64;
typedef void (*func) ();

class A {
public:
    int x; // 4 bytes
    int y; // 4 bytes
    
    int getX() {
        return x;
    }
    virtual void a() {
        std::cout << "A a()\n";
    }
    virtual void b() {
        std::cout << "A b()\n";
    }
    virtual void c() {
        std::cout << "A c()\n";
    }
};

class B : public A {
public:
    int z;
    // int u;
};


int main() {
    std::cout << "sizeof(A)" << sizeof(A) << std::endl;
    std::cout << "sizeof(B)" << sizeof(B) << std::endl;
    printf("%p\n", &A::getX);
    printf("%p\n", &B::getX);
    A a;
    u64 *p = (u64*) &a;
    u64 *arr = (u64*) *p;
    
    func fa = (func) arr[0];
    func fb = (func) arr[1];
    func fc = (func) arr[2];
    fa();
    fb();
    fc();

    A a2;
    printf("%p\n", p);
    p = (u64*) &a2;
    printf("%p\n", p);
    return 0;
}