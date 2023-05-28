#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals;

void foo()
{
    std::cout << std::this_thread::get_id() << std::endl;
}

int main()
{
    // CPU가 지원하는 thread 갯수. static 함수
    int n = std::thread::hardware_concurrency();
    // 8코어 "16"스레드
    std::cout << n << std::endl;

    std::thread t1(&foo);
    std::this_thread::sleep_for(1s);

    std::thread::id tid = t1.get_id();

    std::cout << "created thread id is: " << tid << std::endl;
    std::cout << "main thread id is: " << std::this_thread::get_id() << std::endl;
    
    t1.join();
    return 0;
}