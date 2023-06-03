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
    acc1.m.lock();
    std::this_thread::sleep_for(20ms); // 이를 주면 Deadlock 발생
    acc2.m.lock();
    
    acc1.money -= cnt;
    acc2.money += cnt;
    
    std::cout << "Finish transfer" << std::endl;

    acc1.m.unlock();
    acc2.m.unlock();
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