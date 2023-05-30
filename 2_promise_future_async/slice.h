#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class SliceImage
{
private:
    cv::Mat img;
    cv::Point start_pixel;

public:
    SliceImage(const cv::Mat &_img, const cv::Point &_pixel)
        : img(_img), start_pixel(_pixel)
    {
    }

    // cout overloading
    friend std::ostream &operator<<(std::ostream &os, const SliceImage &si);

    cv::Mat getImg();
    cv::Point getStartPixel();
};

std::vector<std::vector<int>> get_slice_bboxes(cv::Mat &image,
                                               int slice_width,
                                               int slice_height,
                                               float overlap_width_ratio,
                                               float overlap_height_ratio,
                                               int x_start = 0,
                                               int y_start = 0,
                                               bool single_row = true);

std::vector<SliceImage> slice_image(cv::Mat &image,
                                    int slice_widthc,
                                    int slice_height,
                                    float overlap_width_ratio,
                                    float overlap_height_ratio,
                                    bool debug,
                                    int x_start = 0,
                                    int y_start = 0,
                                    bool single_row = true);