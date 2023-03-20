#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

/*
// 기존 멤버 함수에서 try_lock_for, try_lock_until 함수가 추가됨 
2. std::timed_mutex
*/

std::timed_mutex m;
int share_data;

void foo()
{
    // m.lock(); // 기본적으로 blocking
    if (m.try_lock_for(1ms)) // mutex를 잡을 수 있었다면 true
    { 
        share_data = 100;
        std::cout << "using share data" << std::endl;
        std::this_thread::sleep_for(3ms); // 이를 추가했을 때는 획득 실패
        m.unlock();
    }
    else
    {
        std::cout << "뮤텍스 획득 실패" << std::endl;
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);

    t1.join();
    t2.join();
}
