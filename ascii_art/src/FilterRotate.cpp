#include "FilterRotate.hpp"

void FilterRotate::apply(std::pair<std::unique_ptr<Image>, Img> &image)
{
    Image &img = *image.first;
    int width = img.width;
    int height = img.height;
    std::vector<unsigned char> temp(width * height);

    switch (image.second.rotate)
    {
    case 90:
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                temp[x * height + (height - y - 1)] = img.data[y * width + x];
            }
        }
        std::swap(img.width, img.height);
        break;
    case 180:
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                temp[(height - y - 1) * width + (width - x - 1)] = img.data[y * width + x];
            }
        }
        break;
    case 270:
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                temp[(width - x - 1) * height + y] = img.data[y * width + x];
            }
        }
        std::swap(img.width, img.height);
        break;
    }
    img.data = std::move(temp);
}