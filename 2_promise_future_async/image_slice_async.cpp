#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
#include <string>
#include <numeric>
#include <random>
#include <opencv2/opencv.hpp>
#include "slice.h"

static const int NUM = 1'000'000'000;

std::vector<short> v1, v2;

void fill_vector()
{
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> dist(0, 100);

    v1.reserve(NUM);
    v2.reserve(NUM);

    for (int i = 0; i < NUM; i++)
    {
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
    auto ft1 = std::async([]
                          { return std::inner_product(&v1[0], &v1[v1.size() / 4], &v2[0], 0LL); });
    auto ft2 = std::async([]
                          { return std::inner_product(&v1[v1.size() / 4], &v1[v1.size() / 4 * 2], &v2[v1.size() / 4], 0LL); });
    auto ft3 = std::async([]
                          { return std::inner_product(&v1[v1.size() / 4 * 2], &v1[v1.size() / 4 * 3], &v2[v1.size() / 4 * 2], 0LL); });
    auto ft4 = std::async([]
                          { return std::inner_product(&v1[v1.size() / 4 * 3], &v1[v1.size()], &v2[v1.size() / 4 * 3], 0LL); });

    return ft1.get() + ft2.get() + ft3.get() + ft4.get();
}

void measure_execution_time(std::string name, long long (*f)())
{
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    long long result = f();
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    std::cout << name << " : " << result << ", " << time_span.count() << " seconds" << std::endl;
}

int main()
{
    double sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        std::string img_path = "../vessel.jpg";
        cv::Mat img = cv::imread(img_path);

        if (img.empty())
        {
            std::cout << "Read image file fail" << std::endl;
            return -1;
        }

        cv::resize(
            img,
            img,
            cv::Size(1920, 540));

        auto start = std::chrono::system_clock::now();

        // Slice the input image
        std::vector<SliceImage> sliced_image_result = slice_image(
            img,
            704,
            320,
            0.1f,
            0.1f,
            true, // Flag to enable debug information for the slice
            0,
            180);

        cv::Rect bounds(0, 0, img.cols, img.rows);
        cv::Rect rect(0, 0, img.cols, img.rows);
        cv::Mat roi = img(rect & bounds);
        cv::Point start_pixel(0, 0);
        sliced_image_result.emplace_back(
            SliceImage(std::move(roi), start_pixel));

        auto end = std::chrono::system_clock::now();

        // std::cout << "slice time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1e3 << "ms\n";
        sum += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    std::cout << "slice time: " << sum / 1000 / 1e3 << "ms\n";
    return 0;
}