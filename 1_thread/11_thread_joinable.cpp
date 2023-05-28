#include <iostream>
#include <thread>

int main()
{
    // ERROR
    // std::thread t;
    // try {
    //     t.join();
    // }
    // catch (const std::exception &e) {
    //     std::cout << "error: " << e.what() << "\n";
    // }

    std::thread t; 
    if (t.joinable()) {
        t.join();
    }
        
    return 0;
}