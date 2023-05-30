#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std::literals;
void add(std::promise<int> &&pm, int a, int b)
{
    std::this_thread::sleep_for(2s);
    // 한번만 set_value가 가능함
    pm.set_value(a+b);
}


int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();
    // std::shared_future<int> shr_ft = pm.get_future();

    std::thread t(add, std::move(pm), 10, 20);

    // "get" 또한 한 번만 호출 가능함. 단, shr_ft는 계속 가능
    std::cout << ft.valid() << "\n";
    auto ret = ft.get();
    // 꺼낸 뒤에는 유효하지 않다고 나옴
    std::cout << ft.valid() << "\n";

    t.join();

    return 0;
}