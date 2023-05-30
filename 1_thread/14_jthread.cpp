#include <chrono>
#include <iostream>
#include <thread>

using namespace std::literals;

void foo()
{
    for (int i=0; i<10; i++) {
        std::this_thread::sleep_for(500ms);
        std::cout << "foo: " << i << std::endl;
    }
}

void goo(std::stop_token token)
{
    for (int i=0; i<10; i++) {
        if (token.stop_requested() ) {
            std::cout << "중지요청\n";
            return ;
        }
        std::this_thread::sleep_for(500ms);
        std::cout << "goo: " << i << std::endl;
    }
}

int main()
{
    std::jthread j1(foo);
    std::jthread j2(goo);

    std::cout << "sleep_for 2s\n";
    std::this_thread::sleep_for(2s); 
    std::cout << "end\n";

    /* 
    jthread는 협력적인 인터럽트 + joining, 총 2가지 역할을 하고 있다
    */
    
    j1.request_stop();
    j2.request_stop();

    return 0;
}

