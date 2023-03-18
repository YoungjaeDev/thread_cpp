#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
#include <string>
#include <numeric>
#include <random>

static const int NUM = 1'000'000'000;

std::vector<short> v1, v2;

void fill_vector()
{
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> dist(0, 100);

    v1.reserve(NUM);
    v2.reserve(NUM);

    for (int i=0; i<NUM; i++) {
        v1.emplace_back(dist(engine));
        v2.emplace_back(dist(engine));
    }
}

long long f1()
{
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0LL);
}

long long f2()
{
    auto ft1 = std::async([] { return std::inner_product(&v1[0], &v1[v1.size()/ 4], &v2[0], 0LL); }); 
    auto ft2 = std::async([] { return std::inner_product(&v1[v1.size()/ 4], &v1[v1.size()/ 4 * 2], &v2[v1.size()/ 4], 0LL); }); 
    auto ft3 = std::async([] { return std::inner_product(&v1[v1.size()/ 4 * 2], &v1[v1.size()/ 4 * 3], &v2[v1.size()/ 4 * 2], 0LL); }); 
    auto ft4 = std::async([] { return std::inner_product(&v1[v1.size()/ 4 * 3], &v1[v1.size()], &v2[v1.size()/ 4 * 3], 0LL); }); 

    return ft1.get() + ft2.get() + ft3.get() + ft4.get();
}

void measure_execution_time(std::string name, long long (*f)()) {
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    long long result = f();
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    std::cout << name << " : " << result << ", " << time_span.count() << " seconds" << std::endl;
    
}

int main()
{
    fill_vector();

    std::cout << "Start... inner product \n";

    measure_execution_time("f1", f1);
    measure_execution_time("f2", f2);
    
    /*
    f1 : 2500008593186, 5.82259 seconds
    f2 : 2500008593186, 0.445459 seconds
    */
    return 0;
}