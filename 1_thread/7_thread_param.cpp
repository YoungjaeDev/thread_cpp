#include <iostream>
#include <thread>
#include <string>

void f1() {}
void f2(int a, double b) {}
void f3(int a, int &b, std::string &&s ) { b = 100;}

int main()
{
    int n = 0;
    std::string s = "hello";

    // std:thread의 생성자는 "가변인자 템플릿"으로 되어 있으므로 인자의 경우 생성자에 전달
    std::thread t1(&f1);
    std::thread t2(&f2, 10, 3.4);
    // 참조를 주는 것은 좋은 표현이 아니다
    // 만일 주 스레드가 죽으면, 스레드에서 잘못 참조한 주소에 값을 넣을 수 있다
    std::thread t3(&f3, 1, std::ref(n), std::move(s));
    
    t1.join();
    t2.join();
    t3.join();

    std::cout << s << "\n"; // 빈 문자열
    std::cout << n << "\n"; // 100

    return 0;
}