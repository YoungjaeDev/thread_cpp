#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std::literals;

void add(std::promise<int> &&p, int a, int b)
{
    // std::this_thread::sleep_for(3s);
    std::this_thread::sleep_for(1s);
    p.set_value(a+b);
}

int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    std::thread t(add, std::move(pm), 10, 20);

    // 무한정 대기
    // auto ret = ft.get();
    // wait_until도 가능
    std::future_status ret = ft.wait_for(2s);

    // 결과값이 도달했다면
    if (ret == std::future_status::ready) {
        std::cout << "Ready! " << std::endl;
    }
    // Thread가 설정한 시간보다 초과한다면
    else if(ret == std::future_status::timeout) {
        std::cout << "Time out! " << std::endl;
    }
    // 연산을 수행할 함수가 아직 시작 안됨
    // "async" 함수에서 사용
    else if(ret == std::future_status::deferred) {
        ;
    }

    t.join();
    return 0;
}