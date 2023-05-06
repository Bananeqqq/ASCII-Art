#ifndef ASCII_ART_IMAGEJPG_HPP
#define ASCII_ART_IMAGEJPG_HPP
#include "Image.hpp"


class ImageJPG : public Image {
public:
    ImageJPG(int width = 0, int height = 0) : Image(width, height, 3) {}
    bool load(const std::string& filename) override;
};


#endif //ASCII_ART_IMAGEJPG_HPP
