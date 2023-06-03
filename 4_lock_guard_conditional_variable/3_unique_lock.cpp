#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std::literals;

std::mutex m1, m2, m3;
std::timed_mutex tm1, tm2, tm3;

/* unique_lock
lock_guard에 대한 기능이 제한되어 있음
- lock, unlock 자동화
- std::adopt_lock으로 이미 lock이 된 mutex를 인자로 받음
*/

int main()
{
    std::unique_lock<std::mutex> u1;
    std::unique_lock<std::mutex> u2(m2); // 생성자에서 m2.lock

    std::unique_lock<std::mutex> u3(m2, std::try_to_lock);
    
    // why?
    if (u3.owns_lock()) {
        std::cout << "acquire mutex" << std::endl;
    }
    else {
        std::cout << "fail to lock" << std::endl;
    }

    m3.lock();
    std::unique_lock<std::mutex> u4(m3, std::adopt_lock); // 이미 lock을 획득한 뮤텍스 관리
 
    std::unique_lock<std::timed_mutex> u5(tm1, std::defer_lock);
    auto ret = u5.try_lock_for(2s);

    std::unique_lock<std::timed_mutex> u6(tm2, 2s); // try_lock_for
    std::unique_lock<std::timed_mutex> u7(tm3, std::chrono::steady_clock::now() + 2s); // try_lock_until

    return 0;
}