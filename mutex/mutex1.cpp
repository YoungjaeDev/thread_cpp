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
    // 지역 변수
    // 스택에 놓인다. 스택은 스레드당 한 개씩 따로 만들어진다
    // 즉, 지역변수는 "스레드에 안전"하다
    int x = 0;

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