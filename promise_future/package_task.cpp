#include <iostream>
#include <thread>
#include <future>
#include <chrono>

// thread를 위해 만들어진 함수가 아닐 때
int add(int a, int b)
{
    std::cout << "function add" << std::endl;
    return a + b;
}

int main()
{   
    std::packaged_task<int(int, int)> task(add);
    std::future<int> ft = task.get_future();

    // promise를 package_task로 대체
    std::thread t(std::move(task), 10, 20);

    auto ret = ft.get();
    std::cout << "ret: " << ret << "\n";

    t.join();
    return 0;
}