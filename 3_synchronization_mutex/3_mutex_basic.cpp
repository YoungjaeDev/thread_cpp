#include <iostream>
#include <string_view>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std::literals;

std::mutex m;

void delay()
{
    std::this_thread::sleep_for(5ms);
}

void foo(std::string_view name)
{
    /* static variable
    data 메모리에 놓이고, 모든 스레드가 공유
    */
    static int x = 0;

    for (int i = 0; i < 10; i++)
    {
        m.lock();
        // ============
        x = 100;
        delay();
        x += 1;
        delay();

        std::cout << name << " : " << x << std::endl;
        // ============
        m.unlock();

        delay();
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