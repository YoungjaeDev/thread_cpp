#include <iostream>
#include <string_view>
#include <thread>
#include <chrono>
#include <mutex>

/*
C++ 표준이 제공하는 mutex 종류
기본 3개에 timed가 붙여진 3개

1. std::mutex [C++11]
2. std::timed_mutex [C++11]
3. std::recursive_mutex [C++11]
4. std::recursive_timed_mutex [C++11]
5. std::shared_mutex [C++17]
6. std::shared_timed_mutex [C++14]
*/

using namespace std::literals;

std::mutex m;
int share_data = 0;

void foo(std::string_view name)
{
    // m.lock();
    if (m.try_lock())
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
    // 원래 하나의 스레드는 mutex 획득 실패를 하지만, 20ms 정도 기다리면 모두 획득 가능
    std::this_thread::sleep_for(20ms);
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