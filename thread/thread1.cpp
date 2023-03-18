#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals;

void foo()
{
    for(int i=0 ; i<10; i++) {
        std::cout << "foo: " << i << std::endl;
        std::this_thread::sleep_for(100ms);
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

    // 주 스레드가 바로 끝난다
    t.detach();

    int n;
    std::cin >> n;

    std::cout << "end" << std::endl;
    return 0;
}