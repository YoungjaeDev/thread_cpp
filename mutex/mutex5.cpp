#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

/*
C++ 표준이 제공하는 mutex 종류
기본 3개에 timed가 붙여진 3개

1. std::mutex
2. std::timed_mutex
3. std::recursive_mutex
4. std::recursive_timed_mutex
5. std::shared_mutex
6. std::shared_timed_mutex
*/

std::mutex m;
int share_data;

void foo()
{
    // m.lock(); // 기본적으로 blocking
    if (m.try_lock()) // mutex를 잡을 수 있었다면 true
    { 
        share_data = 100;
        std::cout << "using share data" << std::endl;
        m.unlock();
    }
    else
    {
        std::cout << "뮤텍스 획득 실패" << std::endl;
    }
}

int main()
{
    // 뮤텍스는 copy & move 둘 다 안됨
    // std::mutex m2 = m; // error
    // std::mutex m3 = std::move(m); // error
    
    std::mutex::native_handle_type h = m.native_handle();

    std::thread t1(foo);
    std::this_thread::sleep_for(10ms);
    std::thread t2(foo);

    t1.join();
    t2.join();
}
