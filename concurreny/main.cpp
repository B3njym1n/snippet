#include <iostream>
#include <thread>
#include <vector>

using namespace std;

int func1(int v);
void func2(int v);

int main(int argc, char* argv[]) {
    /* printf("func1(1) ret %d\n", func1(1));
    printf("func1(2) ret %d\n", func1(2)); */
    vector<thread> ts;
    for (int i = 0; i < 4; ++i)
    {
        // thread t(func2, 1);
        ts.emplace_back(func2, 1);
    }
    for (int i = 0; i < 4;++i) {
        ts[i].join();
    }

    return 0;
}

int func1(int v) {
    // static int start_ = 0;
    int start_ = 0;
    start_ += v;
    return start_;
}

void func2(int v) {
    printf("func1(%d) ret %d\n", v, func1(v));
}