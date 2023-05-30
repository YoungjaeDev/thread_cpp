#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std::literals;

/* std::async의 반환값
- std::future
- 소멸자에서 get()을 호출해서 대기 
- 사용자가 명시적으로 get을 호출하지 않아도 스레드 종료를 대기하게 된다
*/
int add(int a, int b)
{
    std::cout << "Start add" << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << "Finish add" << std::endl;
    return a+b;
}

void foo(std::promise<int>&& p)
{
    std::cout << "Start add" << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << "Finish add" << std::endl;
    p.set_value(10);
}

int main()
{
    std::future<int> ft = std::async(std::launch::async, add, 10, 20);

    /* std::async의 반환 값을 받지 않은 경우
    - 반환값으로 나오는 임시객체가 파괴될 때 소멸자에서 get() 호출
    - 비동기(스레드)로 수행한 함수가 종료될 때까지 주 스레드가 대기하는 효과
    */
    // std::async(std::launch::async, add, 10, 20);

    /*
    단, async로 반환되는 future가 아니면, 자동적으로 get을 불러주지 않는다
    */
    // std::promise<int> pm;
    // std::future<int> ft = pm.get_future();
    // std::thread t(foo, std::move(pm));
    // std::cout << "continue main: " << std::this_thread::get_id() << "\n";
    
    // ft 변수가 삭제될 때, 소멸자에서 자동적으로 get을 호출하게 된다
    ft.get();

    // t.detach();
    // ft.get();

    return 0;
}