#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
// header 추가
// 신호(signal) 기반의 동기화 도구
#include <condition_variable>

using namespace std::literals;

std::mutex m;
int shared_data;
std::condition_variable _cv;

void consumer()
{
    while(1) {
        std::unique_lock<std::mutex> ul(m);

        // 신호가 올 때까지 대기
        // condition_variable을 사용하기 위해서는 unique_lock을 시용해야 한다
        
        // 내부 동작
        // 1. ul에 대한 lock을 푼다
        // 2. 신호가 올 때까지 대기
        // 3. 다시 내부적으로 lock을 건다
        _cv.wait( ul );

        std::cout << "consume: " << shared_data << std::endl;
        std::this_thread::sleep_for(1s);
    }
}

void producer()
{
    while(1) {
        {
            // 중괄호가 없으면 또 해당 lock, unlock이 반복됨
            std::lock_guard<std::mutex> lg(m);
            shared_data = shared_data + 1;
            std::cout << "produce" << std::endl;
        } 
        _cv.notify_one();
        std::this_thread::sleep_for(1s);
    }
}

int main()
{
    std::thread t1(consumer);
    std::thread t2(producer);
    
    t1.join();
    t2.join();

    return 0;   
}