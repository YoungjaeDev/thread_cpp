#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std::literals;

// std::future, 소멸자에서 get 호출을 대기
// 사용자가 명시적으로 get을 하지 않아도 소멸자에서 스레드 종료를 대기하게 된다
// 동일하게 async로 실행해도 대기를 하게 된다
int add(int a, int b)
{
    std::cout << "Start add" << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << "Finish add" << std::endl;
    return a+b;
}

int main()
{
    std::future<int> ft = std::async(std::launch::async, add, 10, 20);

    std::cout << "continue main: " << std::this_thread::get_id() << "\n";
    
    // ft.get();
    
    return 0;
}