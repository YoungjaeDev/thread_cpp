#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std::literals;

std::mutex m;

void foo()
{
    m.lock();
    // std::adopt_lock
    // 이미 lock을 획득한 상태에서, lock_guard로 만드려고 할 때 사용 (자동으로 unlock)
    std::lock_guard<std::mutex> lg(m, std::adopt_lock);
    std::cout << "using shared data" << std::endl;
  
}

void goo()
{
    try {
        foo();
    }
    catch(...)
    {
        std::cout << "Occur exception" << std::endl;
    }
}

int main()
{
    std::thread t1(foo);

    t1.join();

    return 0;
}