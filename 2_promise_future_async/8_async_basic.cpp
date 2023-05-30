#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std::literals;

// 함수를 비동기(스레드)로 실행하려면
/*
1. std::thread 사용
2. std::jthread 사용 (C++20 이후)
3. std::async 사용

이번에는 std::async
1. 주어진 함수를 비동기로 수행하는 함수 템플릿
2. 기존에 작성된 함수를 간단하게 스레드로 수행할 수 있음 -----> package_task와 밀접
3. 일반적인 구현은 스레드 풀 사용 (스레드 관리에 있어서 사용자가 관여할 수고를 덜 수 있어서 용이)
4. std::future 반환
*/

int add(int a, int b)
{
    std::cout << "Add thread id: " << std::this_thread::get_id() << "\n";
    std::this_thread::sleep_for(2s);
    return a+b;
}

int main()
{
    std::cout << "main thread id: " << std::this_thread::get_id() << "\n";
    // 반환값은 ft로 받을 수 있음
    std::future<int> ft = std::async(add, 10, 20);

    std::cout << "continue main " << std::endl;

    int ret = ft.get();

    std::cout << ret << "\n";
    return 0;
}