#include <iostream>
#include <string_view>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std::literals;

// timed_mutex는 별도로 멤버 함수로 try_lock_until과 try_lock_for 함수를 가지고 있음
std::timed_mutex m;
int share_data = 0;

void foo(std::string_view name)
{
    // m.lock();
    if (m.try_lock_for(20ms))
    {
        share_data = 100;
        std::cout << "using share_data" << std::endl;
        m.unlock();
    }
    else
    {
        std::cout << "mutex 획득 실패" << std::endl;
    }
}

int main()
{
    std::thread t1(foo, "A");
    std::thread t2(foo, "B");

    if (t1.joinable())
    {
        t1.join();
    }
    if (t2.joinable())
    {
        t2.join();
    }

    return 0;
}