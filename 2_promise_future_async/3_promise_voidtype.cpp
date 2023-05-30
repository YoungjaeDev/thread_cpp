#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>
#include <numeric>

int main()
{
    std::vector<int> v1 = { 1,2, 3, 4,5,6,7,8,9,10};
    std::vector<int> v2(10);

    // 작업이 끝났다는 것을 알리는 용도이기 때문에 void로 선언가능
    std::promise<void> pm;
    // 이것은 값을 반환 받아야 하기 때문에
    std::promise<int> pm2;
    std::future<void> f = pm.get_future();
    std::future<int> f2 = pm2.get_future();

    
    std::thread t([&]{
        // 부분 합
        std::partial_sum(v1.begin(), v1.end(), v2.begin());

        // void 형태의 promise기 때문에 아래 동작이 가능
        pm.set_value();

        int s = std::accumulate(v2.begin(), v2.end(), 0);

        pm2.set_value(s);
    });
    
    f.get();

    for (auto n : v2) {
        std::cout << n << ", ";
    }

    auto ret = f2.get();

    std::cout << "\n" << ret << std::endl;

    if (t.joinable()) {
        t.join();
    }
    return 0;
}