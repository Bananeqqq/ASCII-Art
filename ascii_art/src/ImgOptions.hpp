#ifndef ASCII_ART_IMGOPTIONS_HPP
#define ASCII_ART_IMGOPTIONS_HPP

#include <string>

struct Img {
    std::string image_path;
    std::string charset;
    double brightness = 0.0;
    double scale = 1.0;
    bool invert = false;
    int rotate = 0;
    bool flip_horizontal = false;
    bool flip_vertical = false;
};
#endif //ASCII_ART_IMGOPTIONS_HPP
