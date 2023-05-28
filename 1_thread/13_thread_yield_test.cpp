#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals;

void foo1()
{
    while (true) {
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "foo1\n";

        std::this_thread::sleep_for(std::chrono::seconds(1) - (std::chrono::high_resolution_clock::now() - start));
        // while (std::chrono::high_resolution_clock::now() - start < std::chrono::seconds(1)) {
        //     std::this_thread::yield();
        // }
    }
}

void foo2()
{
    while (true) {
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "foo2\n";

        std::this_thread::sleep_for(std::chrono::seconds(1) - (std::chrono::high_resolution_clock::now() - start));
        // while (std::chrono::high_resolution_clock::now() - start < std::chrono::seconds(1)) {
        //     std::this_thread::yield();
        // }
    }
}

void foo3()
{
    while (true) {
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "foo3\n";

        std::this_thread::sleep_for(std::chrono::seconds(1) - (std::chrono::high_resolution_clock::now() - start));
        // while (std::chrono::high_resolution_clock::now() - start < std::chrono::seconds(1)) {
        //     std::this_thread::yield();
        // }
    }
}

void foo4()
{
    while (true) {
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "foo4\n";

        std::this_thread::sleep_for(std::chrono::seconds(1) - (std::chrono::high_resolution_clock::now() - start));
        // while (std::chrono::high_resolution_clock::now() - start < std::chrono::seconds(1)) {
        //     std::this_thread::yield();
        // }
    }
}

int main()
{
    std::thread t1(&foo1);
    std::thread t2(&foo2);
    std::thread t3(&foo3);
    std::thread t4(&foo4);
    
    if (t1.joinable()) {
        t1.join();
    }
    if (t2.joinable()) {
        t2.join();
    }
    if (t3.joinable()) {
        t3.join();
    }
    if (t4.joinable()) {
        t4.join();
    }

    return 0;
}
