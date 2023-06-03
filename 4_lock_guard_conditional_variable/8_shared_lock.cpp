#include <iostream>
#include <thread>
#include <chrono>
#include <shared_mutex>
#include <string_view>

using namespace std::literals;

std::shared_mutex m;
int share_data = 0;

// lock_guard를 사용할 때는 중괄호를 써야할 것 같음
// 안그러면 계속 획득 / 반환을 한 스레드에서 반복하는 현상이 발생함
void Writer()
{
    while(1) {
        auto start_time = std::chrono::steady_clock::now();
        // m.lock(); // blocking
        {
            std::lock_guard<std::shared_mutex> lg(m);
            auto end_time = std::chrono::steady_clock::now();
            auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
            std::cout << "Lock acquired in " << elapsed_time << "ms\n";

            share_data = share_data + 1;
            std::cout << "Writer : " << share_data << "\n";
            std::this_thread::sleep_for(1s);
        }
        // m.unlock();
        std::this_thread::sleep_for(10ms);
    }
}

void Reader()
{
    while(1) {
        {
            std::shared_lock<std::shared_mutex> lg(m);
            // m.lock_shared();
            std::cout << "Reader : " << share_data << "\n";
            std::this_thread::sleep_for(1s);
            // m.unlock_shared();
        }
        std::this_thread::sleep_for(10ms);
    }
}

int main()
{
    /*
    - 쓰는 동안에는 읽을 수 없어야 한다
    - 읽는 동안에도 쓸 수 없어야 한다
    - 하나의 스레드가 읽는 동안 다른 스레드도 읽을 수 있다
    */
    std::thread t1(Writer);
    std::thread t2(Reader);
    std::thread t3(Reader);
    std::thread t4(Reader);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    return 0;
}