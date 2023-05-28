#include <iostream>
#include <thread>

/* thread 헤더
std::this_thread::get_id - 현재 스레드의 ID 반환
std::this_thread::sleep_for - 주어진 시간만큼 현재 스레드 재우기
std::this_thread::sleep_until - 주어진 시간까지 현재 스레드 재우기
std::this_thread::yield - 다른 스레드를 실행할 수 있도록 힌트 제공
*/

int main()
{
    // 실행중인 현재 스레드 ID 반환
    std::cout << std::this_thread::get_id() << std::endl;
    
    /* std::thread::id
    - 스레드 ID를 나타내는 가벼운 구조체
    - cout으로 출력 가능하고, 비교 연산 가능
    - 정수로 변환이 안됨. std::hash<std::thread::id> 함수객체가 제공되므로, unordered 컨테이너에 키 값으로 사용 가능
    */
    std::thread::id tid1 = std::this_thread::get_id();
    std::thread::id tid2 = std::this_thread::get_id();
    
    tid1 == tid2;
    tid1 < tid2;
    
    std::hash<std::thread::id> h;

    std::cout << h(tid1) << std::endl;
    std::cout << h(tid2) << std::endl;
    
    return 0;
}
