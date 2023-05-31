#include <iostream>
#include <string_view>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std::literals;

std::recursive_mutex m;
int share_data = 0;

void foo(std::string_view name)
{
    /*
    std::recursive_mutex
    // 하나의 스레드가 "여러번 뮤텍스 소유" 가능
    // 내부적으로 횟수를 관리
    // 단, 소유한 횟수만큼 unlock를 해야 한다
    */
    m.lock(); // 기존 mutex는 한 번만 뮤텍스를 소유할 수 있다
    m.lock();
    share_data = 100;
    std::cout << "using share_data" << std::endl;
    m.unlock();
    
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