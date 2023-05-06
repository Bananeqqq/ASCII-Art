#include "Image.hpp"
#include <cmath>


std::string Image::imgToAscii(float scaleFactor) const {
    std::string ascii_image;
    const std::string charset = " .'`^,:;Il!i><~+_-?][}{1)(|/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    auto scaledWidth = static_cast<unsigned int>(width * scaleFactor);
    auto scaledHeight = static_cast<unsigned int>(height * scaleFactor);

    for (unsigned int y = 0; y < scaledHeight; ++y) {
        for (unsigned int x = 0; x < scaledWidth; ++x) {
            unsigned int scaledX = x / scaleFactor;
            unsigned int scaledY = y / scaleFactor;
            unsigned int index = (scaledY * width + scaledX) * num_channels;
            auto r = data[index];
            auto g = data[index + 1];
            auto b = data[index + 2];
            if (num_channels==4) {
                auto a = data[index + 3];
                if (a == 0) {
                    ascii_image += ' ';
                    continue;
                }
            }

            double gamma = 2.0f;
            //Normalized graylevel approximation, recommendation from the Charles Poynton's Color (Copyright (c) 1998-01-04 Charles Poynton poynton@inforamp.net)
            double brightness = (0.212671f * pow(r / 255.0f, gamma) + 0.715160f * pow(g / 255.0f, gamma) + 0.072169f * pow(b / 255.0f, gamma));
            unsigned int idx = (double)(brightness * (charset.length() - 1));
            ascii_image += charset[idx];
        }
        ascii_image += '\n';
    }
    return ascii_image;
}