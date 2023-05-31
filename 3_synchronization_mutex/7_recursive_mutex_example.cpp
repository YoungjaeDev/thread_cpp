#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

class Machine
{
    std::recursive_mutex m;
    int share_data;

public:
    void foo1()
    {
        m.lock();
        share_data = 200;
        m.unlock();
    }

    void foo2()
    {
        m.lock();
        share_data = 100;
        foo1(); // 하나의 함수에서 또다른 함수를 호출할 수 있기 때문에, 또 이때 mutex를 공유한다면 .. recursive_mutex가 필요
        m.unlock();
    }
};
int main()
{
    Machine mch;
    std::thread t1(&Machine::foo1, &mch);
    std::thread t2(&Machine::foo2, &mch);

    t1.join();
    t2.join();
}
