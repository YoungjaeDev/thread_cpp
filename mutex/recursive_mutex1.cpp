#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

/*
// 기존 mutex는 한 번만 뮤텍스를 소유할 수 있다
// 하나의 스레드가 "여러번 뮤텍스 소유" 가능
// 단, 소유한 횟수만큼 unlock를 해야 한다
3. std::recursive_mutex
*/

// std::mutex m;
std::recursive_mutex m;
int share_data;

void foo()
{
    m.lock();
    m.lock(); // 뮤텍스가 이미 잠겨 있고 잠금 해제될 때까지 다시 잠글 수 없기 때문에 m.lock()에 대한 두 번째 호출에서 스레드가 무기한 차단됩니다.
    std::cout << "Function Foo" << std::endl;
    m.unlock();
    m.unlock();
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);

    t1.join();
    t2.join();
}
