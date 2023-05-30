#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std::literals;

void add(std::promise<int> &&pm, int a, int b)
{
    std::this_thread::sleep_for(2s);
    pm.set_value(a+b);
}

void consume1(std::shared_future<int> sf)
{
    auto ret = sf.get();
    // std::this_thread::sleep_for(1s);
    std::cout << "consume1: " << ret << "\n";
}

void consume2(std::shared_future<int> sf)
{
    auto ret = sf.get();
    std::cout << "consume2: " << ret << "\n";
}

int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();
    // future 객체는 copy가 지원이 안됨
    // 동시에 서로 다른 스레드에서 값을 받고 싶을 때 share를 써서 공유함
    std::shared_future<int> shr_ft = ft.share();

    // std::future를 선언 안하고 바로도 가능
    // std::shared_future<int> shr_ft = pm.get_future();

    std::thread t(add, std::move(pm), 10, 20);

    std::thread t1(consume1, shr_ft);
    std::thread t2(consume2, shr_ft);
    
    t.join();
    t1.join();
    t2.join();
    
    return 0;
}