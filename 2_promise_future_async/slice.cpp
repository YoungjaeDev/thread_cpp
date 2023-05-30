#include "slice.h"
#include <algorithm>
#include <typeinfo>
#include <thread>
#include <future>
#include <mutex>

std::mutex m;

std::ostream &operator<<(std::ostream &os, const SliceImage &si)
{
    os << "img size: " << si.img.size() << ", ";
    os << "start pixel: " << si.start_pixel << "\n";

    return os;
}

// Getter
cv::Mat SliceImage::getImg()
{
    return this->img;
}

cv::Point SliceImage::getStartPixel()
{
    return this->start_pixel;
}


std::vector<std::vector<int>> get_slice_bboxes(cv::Mat &image,
                                               int slice_width,
                                               int slice_height,
                                               float overlap_width_ratio,
                                               float overlap_height_ratio,
                                               int x_start,
                                               int y_start,
                                               bool single_row)
{
    // 원본 이미지 width, height
    auto image_width = image.cols;  // image.size().width
    auto image_height = image.rows; // image.size().height

    std::vector<std::vector<int>> slice_bboxes;
    int x_min, x_max, y_min, y_max;
    float x_overlap, y_overlap;

    y_min = y_start;
    y_max = 0;
    x_overlap = 0.0f;
    y_overlap = 0.0f;

    assert(image_height > 0 and image_width > 0);
    y_overlap = static_cast<int>(overlap_height_ratio * slice_height);
    x_overlap = static_cast<int>(overlap_width_ratio * slice_width);

    while (y_max < image_height)
    {
        x_min = 0;
        x_max = 0;
        y_max = y_min + slice_height;

        while (x_max < image_width)
        {
            x_max = x_min + slice_width;
            // width, height 둘 중 하나가 이미지 끝에 도달헀을 때
            if (y_max > image_height or x_max > image_width)
            {
                auto xmax = std::min(image_width, x_max);
                auto ymax = std::min(image_height, y_max);
                auto xmin = std::max(0, xmax - slice_width);
                auto ymin = std::max(0, ymax - slice_height);
                slice_bboxes.emplace_back(
                    std::vector<int>{xmin, ymin, xmax, ymax});
            }
            else
            {
                slice_bboxes.emplace_back(
                    std::vector<int>{x_min, y_min, x_max, y_max});
            }
            x_min = x_max - x_overlap;
        }

        if (single_row)
        {
            break;
        }
        y_min = y_max - y_overlap;
    }
    // slice 위치에 대한 반환 vector 반환
    return slice_bboxes;
}

std::vector<SliceImage> slice_image(cv::Mat &image,
                                    int slice_width,
                                    int slice_height,
                                    float overlap_width_ratio,
                                    float overlap_height_ratio,
                                    bool debug,
                                    int x_start,
                                    int y_start,
                                    bool single_row)
{
    std::vector<SliceImage> sliced_image_result;

    // slice image time_check
    clock_t start, end;
    double time_used;

    start = clock();

    // BGR로 이미지 읽기
    // (변경예정) 추후 IR일 때도 적용할 수 있도록 파라미터화
    if (debug)
        std::cout << "image size: " << image.size() << "\n";
    assert(image.data != NULL); // not image.empty()
    // num_slice

    int n_ims = 0;

    // xyxy
    int tlx, tly, brx, bry;

    auto slice_bboxes = get_slice_bboxes(image,
                                         slice_width,
                                         slice_height,
                                         overlap_width_ratio,
                                         overlap_height_ratio,
                                         x_start,
                                         y_start,
                                         single_row);

    // Crop Image
    // 방지 OpenCV Error: Assertion failed (0 <= roi.x && 0 <= roi.width && roi.x + roi.width <= m.cols && 0 <= roi.y && 0 <= roi.height && roi.y + roi.height <= m.rows) in cv::Mat::Mat
    cv::Rect bounds(0, 0, image.cols, image.rows);
    
    // Define a lambda function to create a sliced image and add it to the result vector
    auto create_sliced_image = [&](int idx) {
        auto &slice_bbox = slice_bboxes[idx];
        n_ims += 1;
        tlx = slice_bbox[0];
        tly = slice_bbox[1];
        brx = slice_bbox[2];
        bry = slice_bbox[3];

        if (debug)
        {
            std::cout << "slice " << n_ims << ", "
                      << "tlx: " << tlx << ", "
                      << "tly: " << tly << ", "
                      << "brx: " << brx << ", "
                      << "bry: " << bry << "\n";
        }

        cv::Rect rect(tlx, tly, brx - tlx, bry - tly);
        m.lock();
        cv::Mat roi = image(rect & bounds).clone();
        m.unlock();
        cv::Point start_pixel(tlx, tly);

        return SliceImage(std::move(roi), start_pixel);
    };

    // Use std::async to create the sliced images in parallel
    std::vector<std::future<SliceImage>> futures;
    for (int i = 0; i < slice_bboxes.size(); i++)
    {
        futures.emplace_back(std::async(std::launch::async, create_sliced_image, i));
    }

    // Wait for all futures to complete and add the results to the sliced_image_result vector
    for (auto &future : futures)
    {
        sliced_image_result.emplace_back(future.get());

    }

    return sliced_image_result;
}