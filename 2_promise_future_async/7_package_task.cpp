#include <iostream>
#include <thread>
#include <future>
#include <chrono>

// thread를 위해 고려하지 않고, 만들어진 함수를 비동기로 실행하려고 할 때
int add(int a, int b)
{
    std::cout << "function add" << std::endl;
    return a + b;
}

int main()
{   
    // callable object(함수, 함수객체, 람다 등)을 비동기 호출할 수 있도록 래퍼를 만드는 도구
    std::packaged_task<int(int, int)> task(add);
    std::future<int> ft = task.get_future();

    // promise를 package_task로 대체
    std::thread t(std::move(task), 10, 20);

    // Return 값을 가져오게 된다
    auto ret = ft.get();
    std::cout << "ret: " << ret << "\n";

    t.join();
    return 0;
}