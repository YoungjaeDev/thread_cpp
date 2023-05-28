#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals;

void foo()
{
    for(int i=0 ; i<10; i++) {
        std::cout << "foo: " << i << std::endl;
        std::this_thread::sleep_for(100ms);

        // 2. yield
        // auto target = std::chrono::high_resolution_clock::now() + 100ms;

        // while (std::chrono::high_resolution_clock::now() < target) {
        //     std::this_thread::yield(); // 다른 스레드에게 주도권을 넘김 
        // }
    }
}

int main()
{
    std::thread t(&foo);

    // 그냥 실행하면 abort error가 뜬다

    // join vs detach
    // join: 스레드 종료를 대기
    // detach: 스레드를 떼어낸다

    // t.join();

    // 주 스레드가 바로 끝나면 detach된 스레드가 강제로 종료됨
    t.detach();

    // 만일 주 스레드가 어떠한 대기를 하고 있다면?
    int n;
    std::cin >> n;

    // std::cout << "end" << std::endl;
    return 0;
}