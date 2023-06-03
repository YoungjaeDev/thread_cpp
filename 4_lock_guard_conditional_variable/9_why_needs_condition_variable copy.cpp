#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

std::mutex m;
int shared_data;

// 이 코드의 문제점은 실행할 때 반반의 확률로 소비자가 먼저 도착해서 읽는다는 것이다
/* 
그러면 아래와 같은 출력이 지속된다
consume: 0
consume: 0
consume: 0
consume: 0
*/
void consumer()
{
    while(1) {
        std::lock_guard<std::mutex> lg(m);
        std::cout << "consume: " << shared_data << std::endl;
        std::this_thread::sleep_for(1s);
    }
}

void producer()
{
    while(1) {
        std::lock_guard<std::mutex> lg(m);
        shared_data = shared_data + 1;
        std::cout << "produce: " << shared_data << std::endl;
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