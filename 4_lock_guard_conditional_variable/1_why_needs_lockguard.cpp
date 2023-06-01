#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std::literals;

std::mutex m;

/* mutex 사용 시 직접 lock, unlock을 직접 하는 경우
=> 실수로 unlock을 하지 않을 수 있다
=> lock, unlock 사이에 예외가 발생할 수 있다. 그러면 unlock이 발생하지 않을 수 있다

이를 위해서 std::lock_guard 존재
- 생성자에서 lock, 소멸자에서 unlock을 수행하는 도구
- 예외 발생 시 "지역변수는 안전하게 파괴"되므로 unlock 보장
*/

void foo()
{
    // m.lock();
    {
        std::lock_guard<std::mutex> lg(m);
        std::cout << "using shared data" << std::endl;
    }
    // 일찍 unlock을 하고 싶으면 중괄호 안에 넣어도 된다 
    
    // throw std::exception();
    // m.unlock();
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