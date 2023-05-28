#include <iostream>
#include <chrono>
#include <thread>

using namespace std::literals;

int main()
{
    // chrono 라이브러리의 모든 시간 타입은 duration<>의 alias
    // 같은 duration 타입인데, 안에 들어가는 자료형이 다를뿐
    std::chrono::hours h(10);
    std::chrono::minutes m(10);
    std::chrono::seconds s1(10);
    std::chrono::milliseconds s2(10);
    std::chrono::microseconds s3(10);
    std::chrono::nanoseconds s4(10);

    std::cout << s1.count() << std::endl;

    // namespace std::literals;
    auto a1 = 10s;
    auto a2 = 10ms;
    auto a3 = 10min;

    std::this_thread::sleep_for(std::chrono::duration<long long>(10)); //<long long> -> Seconds
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::this_thread::sleep_for(10s);
    
    return 0;
}