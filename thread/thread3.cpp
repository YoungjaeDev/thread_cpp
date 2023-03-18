// 스레드와 callable object

#include <iostream>
#include <thread>

// 일반 함수 뿐 아니라 다양한 함수를 스레드로 수행할 수 있다
void foo(int a, double d) {}

struct Machine
{
    void Run(int a, double d) {}
};

struct Work
{
    void operator()(int a, double d) const {}
};

int main()
{
    Machine m;
    Work w;

    std::thread t1(&foo, 1, 3.4);
    std::thread t2(&Machine::Run, m, 1, 3.4);
    std::thread t3(w, 1, 3.4);
    std::thread t4([] { std::cout << "Lambda" << std::endl; });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    

    return 0;
}