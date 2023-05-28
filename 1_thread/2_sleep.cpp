#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals;

std::chrono::system_clock::time_point
createDateTime(int year, int month, int day, int hour, int minute, int second);

int main()
{
    // sleep_for: 주어진 시간 만큼 현재 스레드 멈추기
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    // std::this_thread::sleep_for(3s); // 3ms, 3ns, 3min 가능 // std::literals 선언해야 사용 가능
    // std::this_thread::sleep_for(3);

    // sleep_until: 주어진 시간까지 현재 스레드 멈추기
    // std::chrono::time_point tp1 = std::chrono::steady_clock::now();
    // std::cout << "tp1: " << tp1.time_since_epoch().count() << "\n";
    // std::this_thread::sleep_until(tp1 + 2000ms); // 지금 시간보다 2초 뒤까지 재우기
    // std::chrono::time_point tp2 = std::chrono::steady_clock::now();
    // std::cout << "tp2: " << tp2.time_since_epoch().count() << "\n";

    // std::chrono::system_clock::time_point tp1 = std::chrono::system_clock::now();
    // std::cout << "tp1: " << tp1.time_since_epoch().count() << "\n";
    // std::this_thread::sleep_until(tp1 + 2000ms); // 지금 시간보다 2초 뒤까지 재우기
    // std::chrono::system_clock::time_point tp2 = std::chrono::system_clock::now();
    // std::cout << "tp1: " << tp2.time_since_epoch().count() << "\n";

    // auto tp2 = createDateTime(2023, 3, 18, 10, 00, 00);
    // std::this_thread::sleep_until(tp2);
    return 0;
}

time_t toUTC(std::tm &timeinfo)
{
#ifdef _WIN32
    std::time_t tt = _mkgmtime(&timeinfo);
#else
    time_t tt = timegm(&timeinfo);
#endif
    return tt;
}

std::chrono::system_clock::time_point
createDateTime(int year, int month, int day, int hour, int minute, int second)
{
    tm timeinfo1 = tm();
    timeinfo1.tm_year = year - 1900;
    timeinfo1.tm_mon = month - 1;
    timeinfo1.tm_mday = day;
    timeinfo1.tm_hour = hour;
    timeinfo1.tm_min = minute;
    timeinfo1.tm_sec = second;
    tm timeinfo = timeinfo1;
    time_t tt = toUTC(timeinfo);
    return std::chrono::system_clock::from_time_t(tt);
}