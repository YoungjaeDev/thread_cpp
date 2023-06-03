#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std::literals;

std::mutex m;
int shared_data;
std::condition_variable _cv;
bool data_ready = false;
bool data_processs = false;

void consumer()
{
    while(1) 
    {
        std::unique_lock<std::mutex> ul(m);

        _cv.wait( ul , [](){ return data_ready; } );
        data_ready = false;

        std::cout << std::this_thread::get_id() << ", consume: " << shared_data << std::endl;
        
        data_processs = true;
        ul.unlock();
        _cv.notify_one();
    }
    std::this_thread::sleep_for(1s);
}

void producer()
{
    while(1) {
        {
            std::lock_guard<std::mutex> lg(m);
            shared_data = shared_data + 1;
            std::cout << "produce" << std::endl;
        } 
        data_ready = true;
        _cv.notify_all();

        {
            std::unique_lock<std::mutex> ul(m);

            _cv.wait(ul, [](){return data_processs;});
            data_processs = true;
        }
        std::this_thread::sleep_for(1s);
    }
}

int main()
{
    std::thread t1(producer);

    std::thread t2(consumer);
    std::thread t3(consumer);
    std::thread t4(consumer);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;   
}