#include <iostream>
#include <thread>
#include <mutex>
// 추가의 별도 헤더가 있어서 포함시켜야 함
#include <shared_mutex>
#include <chrono>
#include <string_view>

using namespace std::literals;

std::shared_mutex m;
int share_data;

void Writer()
{
    while(1)
    {
        m.lock();
        share_data = share_data + 1;
        std::cout << "Writer: " << share_data << std::endl;
        std::this_thread::sleep_for(1s);
        m.unlock();
        std::this_thread::sleep_for(10ms);
    }
}

void Reader(std::string_view name)
{
    while(1)
    {
        m.lock_shared();
        std::cout << "Reader(" << name << ") : " << share_data << std::endl;
        std::this_thread::sleep_for(500ms);
        m.unlock_shared();
        std::this_thread::sleep_for(10ms);
    }
}

int main()
{
    // 쓰는 동안 읽을 수 없어야 한다
    // 읽는 동안 쓸 수 없어야 한다

    // 단, 하나의 스레드가 읽는 동안 다른 스레드도 읽어도 된다!
    // 이 때 shared_mutex 사용 가능
    std::thread t(Writer);
    std::thread t1(Reader, "A");
    std::thread t2(Reader, "B");
    std::thread t3(Reader, "C");
    t.join();
    t1.join();
    
    return 0;
}