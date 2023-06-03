#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std::literals;

struct Account
{
    std::mutex m;
    int money = 100;
};

void transfer(Account &acc1, Account &acc2, int cnt)
{
    // scoped_lock (Since C++17)
    // std::lock + lock_guard
    // scoped_lock은 가변인자라서 무수히 많은 mutex를 넣을 수 있다
    // C++17에서 템플릿 인자 추론도 가능해서 생략 가능
    std::scoped_lock lg(acc1.m, acc2.m);
    acc1.money -= cnt;
    acc2.money += cnt;
    
    std::cout << "Finish transfer" << std::endl;
}

int main()
{
    Account kim, lee;

    std::thread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::thread t2(transfer, std::ref(lee), std::ref(kim), 5);
    
    /*
    Deadlock 발생 가능성이 있음
    - 서로 acc1에 대한 mutex를 취득한 이후에, 
    - acc2에 대한 mutex는 서로 가져있기 때문에 blocking 되어 있음
    */

    t1.join();
    t2.join();

    return 0;
}