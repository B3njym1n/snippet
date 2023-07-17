#include <iostream>

class Foo {
    public:
    int foo;
    ~Foo() {
        printf("Foo detructor\n");
    }
};

int main()
{
    Foo&& foo = static_cast<Foo&&> (Foo{});
    return 0;
}