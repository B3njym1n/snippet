#include <iostream>
#include <vector>

using namespace std;

vector<int> getPrimes(int q) {
    vector<int> primes(q);
    int i = 1;
    primes[0] = 2;
    int num = 3;
    while (i < q) {
        bool flag = true;
        for (int j = 2; j*j <= num; ++j) {
            if (num % j == 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            primes[i] = num;
            i++;
        }
        num++;
    }
    
    return primes;
}

int main()
{
    auto lst = getPrimes(10);
    for (int e : lst) {
        cout << e << " ";
    }
    cout << '\n';
    return 0;
}