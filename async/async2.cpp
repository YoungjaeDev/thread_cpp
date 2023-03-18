#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std::literals;

int add(int a, int b)
{
    std::cout << "Add thread id: " << std::this_thread::get_id() << "\n";
    std::this_thread::sleep_for(2s);
    return a+b;
}

int main()
{
    // std::future<int> ft = std::async(std::launch::async, add, 10, 20);

    // get을 부를 때 호출됨
    // std::future<int> ft = std::async(std::launch::deferred, add, 10, 20);
    
    // 기본 옵션, 실행하려는 HW(PC, 임베디드, 모바일)에 따라서 어떻게 동작할지 다르다
    // PC는 보통 async로 동작
    std::future<int> ft = std::async(std::launch::async | std::launch::deferred, add, 10, 20);
    
    std::cout << "Continue main: " << std::this_thread::get_id() << std::endl;

    int ret = ft.get();

    std::cout << "Result: " << ret << std::endl;

    return 0;
}