#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std::literals;

void divide(std::promise<int>&& p, int a, int b)
{
    try {
        if ( b == 0 ) 
            throw std::runtime_error("divide by zero");
        p.set_value( a / b); // 0으로 나눈다고 해서 c++ 표준에서는 catch로 안넘겨줌
        // 따라서 이 예제에서는 직접 runtime_error로 넘겨줌
    }
    catch(...)
    {
        std::cout << "Occur exception" << std::endl;
        // 즉시 exception 발생
        // p.set_exception(std::current_exception());
        // 스레드가 종료되었을 때 발생
        p.set_exception_at_thread_exit(std::current_exception());
    }
}

int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    std::thread t(divide, std::move(pm), 10, 0);
    try {
        auto ret = ft.get();
    }
    catch(std::exception& e) {
        std::cout << e.what() << "\n";
    }

    if(t.joinable()){
        t.join();
    }
    return 0;
}