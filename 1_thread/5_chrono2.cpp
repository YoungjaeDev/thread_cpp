#include <iostream>
#include <chrono>
#include <thread>

using namespace std::literals;

int main()
{
    // time_point : 기준 시간 + duration
    // 기준 시간 ( epoch time ): 1970년 1월 1일

    std::chrono::time_point tp1 = std::chrono::system_clock::now();

    // [기준 시간 ( epoch time ): 1970년 1월 1일]으로부터 몇시간이 지났는지?
    std::chrono::hours h = std::chrono::duration_cast < std::chrono::hours > (tp1.time_since_epoch());

    std::cout << h.count() << std::endl;

    std::this_thread::sleep_for(3ms);
    std::this_thread::sleep_until(std::chrono::system_clock::now() + 200ms);
    return 0;
}