#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals;

void mysleep(std::chrono::microseconds us)
{
    auto target = std::chrono::high_resolution_clock::now() + us;

    while (std::chrono::high_resolution_clock::now() < target) {
        std::this_thread::yield();
    }
}

int main()
{
    mysleep(10ms);
}