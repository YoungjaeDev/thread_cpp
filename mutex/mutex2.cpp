#include <iostream>
#include <thread>
#include <chrono>
#include <string_view>

using namespace std::literals;

void delay()
{
    std::this_thread::sleep_for(20ms);
}

void foo(std::string_view name)
{
    // 만일 static 변수라면
    // data 메모리에 놓인다
    // 모든 스레드가 공유한다
    // static 변수는 스레드에 안전하지 않다
    static int x = 0;

    for (int i = 0; i < 10; i++)
    {
        x = 100;
        delay();
        x = x + 1;
        delay();

        std::cout << name << " : " << x << std::endl;

        delay();
    }
}

int main()
{
    std::thread t1(foo, "A");
    std::thread t2(foo, "\tB");

    t1.join();
    t2.join();

    return 0;
}