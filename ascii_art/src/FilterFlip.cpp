#include "FilterFlip.hpp"
#include <algorithm>
#include <sstream>
#include <deque>
#include <numeric>


void FilterFlip::apply(std::pair<std::unique_ptr<Image>, Img> &image) {
    Image& img = *image.first;
    int width = img.width;
    int height = img.height;

    if (image.second.flip_horizontal) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width / 2; ++x) {
                std::swap(img.data[y * width + x], img.data[y * width + (width - x - 1)]);
            }
        }
    }
    if (image.second.flip_vertical) {
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height / 2; ++y) {
                std::swap(img.data[y * width + x], img.data[(height - y - 1) * width + x]);
            }
        }
    }
}
