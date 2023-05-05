#ifndef ASCII_ART_IMAGEPNG_HPP
#define ASCII_ART_IMAGEPNG_HPP
#include "Image.hpp"


class ImagePNG : public Image {
public:
    ImagePNG(int width = 0, int height = 0) : Image(width, height, 4) {}
    bool load(const std::string& filename) override;

};


#endif //ASCII_ART_IMAGEPNG_HPP
