#include <iostream>
#include <vector>
#include <cmath>

int main(int argc, char **argv)
{
    // primes under 1000
    std::vector<bool> A(1000, true);
    A[0] = false;
    A[1] = false;
    int sqrtupper = floor(sqrt(1000));
    for (int i = 2; i <= sqrtupper; ++i)
    {
        if (A[i] == true)
        {
            for (int j = i*i; j < 1000; j+=i) {
                A[j] = false;
            }
        }
    }

    // get9th
    int count = 9;
    int value = 0;
    for (int i = 0; i < 1000 && count > 0; i++)
    {
        if (A[i] == true) {
            value = i;
            printf("%dth prime is %d\n", 9 - count + 1, value);
            count--;
        }
    }
    // printf("9th prime is %d\n", value);
    return 0;
}