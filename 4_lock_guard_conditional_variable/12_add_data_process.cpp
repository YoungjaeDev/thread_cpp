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
bool data_ready = false;
bool data_processs = false;

void consumer()
{
    while(1) 
    {
        std::unique_lock<std::mutex> ul(m);

        // 내부 동작
        // 1. ul에 대한 lock을 푼다
        // 2. 신호가 올 때까지 대기
        // 3. 다시 내부적으로 lock을 건다
        // 4. 치명적인 단점은 
        /*
        생산자에서 notify_one을 하는 순간 wait를 안하고 있으면 이 또한 Sync가 맞지 않게 된다
        consume: 116
        produce
        produce
        consume: 118
        */
       // 두번째 인자로 조건문을 넣음
       // false면 wait 대기
        _cv.wait( ul , [](){ return data_ready; } );
        data_ready = false;

        std::cout << "consume: " << shared_data << std::endl;
        
        data_processs = true;
        ul.unlock();
        _cv.notify_one();
    }
    std::this_thread::sleep_for(100ms);
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
        data_ready = true;
        _cv.notify_one();

        {
            std::unique_lock<std::mutex> ul(m);

            _cv.wait(ul, [](){return data_processs;});
            data_processs = true;
        }
        std::this_thread::sleep_for(50ms);
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