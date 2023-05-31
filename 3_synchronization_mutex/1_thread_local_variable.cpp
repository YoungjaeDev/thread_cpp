#include <iostream>
#include <string_view>
#include <thread>
#include <chrono>

using namespace std::literals;

void delay()
{
    std::this_thread::sleep_for(20ms);
}

void foo(std::string_view name)
{
    /*
    지역변수
    - 스택에 놓인다
    - 스택은 스레드당 한개씩 따로 만들어진다
    - 지역변수는 "스레드에 안전"하다
    */
    int x = 0;

    for (int i = 0; i < 10; i++)
    {
        x = 100;
        delay();
        x += 1;
        delay();

        std::cout << name << " : " << x << std::endl;
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