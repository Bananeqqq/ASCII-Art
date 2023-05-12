#include "Image.hpp"
#include <cmath>



void Image::imgToAscii(const double scaleFactor, const std::string charset, const double brightness) {
    int scaledWidth = width * scaleFactor;
    int scaledHeight = height * scaleFactor;

    if (data.size() < width*height){
        std::cout << "Image: Error while converting to ascii" << std::endl;
        return;
    }

    for (int y = 0; y < scaledHeight; ++y) {
        for (int x = 0; x < scaledWidth; ++x) {
            int scaledX = x / scaleFactor;
            int scaledY = y / scaleFactor;
            int index = scaledY * width + scaledX;
            auto pixel = data[index];

            double gray_level = pow(pixel / 255.0, brightness);
            int idx = (double)(gray_level * (charset.length() - 1));
            ascii_image += charset[idx];
        }
        ascii_image += '\n';
    }
}

