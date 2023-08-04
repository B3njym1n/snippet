#include <iostream>

template<bool a>
int reversed_binary_value() {
    return a;
}

template <bool first, bool second, bool... digits>
int reversed_binary_value() {
    return reversed_binary_value<second, digits...>() * 2 + first;
}

int main() {
    int x = reversed_binary_value<0,0,1,0,1>();
    printf("%d\n", x);
}