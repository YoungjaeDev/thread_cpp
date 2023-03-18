#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std::literals;

// promise
// 스레드 사이에서 "값 또는 예외를 공유" 할 수 있는 템플릿
// promise를 통해서 전달된 데이터는 std::future<>를 통해서 얻을 수 있다


// promise 객체는 &, &&로 전달해야 함
void add(std::promise<int> &&p, int a, int b)
{
    int s = a + b;
    std::this_thread::sleep_for(1s);
    p.set_value(s); // 즉시 값 반환
    // p.set_value_at_thread_exit(s);
    std::cout << "add \n";
    std::this_thread::sleep_for(3s);
}

int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    std::thread t(add, std::move(pm), 10, 20);
    int ret = ft.get(); // blocking 
    std::cout << ret << "\n";
    if (t.joinable()) {
        t.join();
    }

    return 0;
}

