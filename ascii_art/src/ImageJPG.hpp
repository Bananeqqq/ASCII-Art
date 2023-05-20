#ifndef ASCII_ART_IMAGEJPG_HPP
#define ASCII_ART_IMAGEJPG_HPP
#include "Image.hpp"

/**
 * @brief Class for loading JPG images
 */
class ImageJPG : public Image {
public:
    ImageJPG(int width = 0, int height = 0) : Image(width, height) {}
    bool load(const std::string& filename, bool inverted) override;
};


#endif //ASCII_ART_IMAGEJPG_HPP
