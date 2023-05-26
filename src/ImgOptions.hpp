#ifndef ASCII_ART_IMGOPTIONS_HPP
#define ASCII_ART_IMGOPTIONS_HPP

#include <string>

/**
 * @brief Struct for storing the configuration of an image
 */
struct Img
{
    std::string image_path;
    std::string charset = " .'`^,:;Il!i><~+_-?][}{1)(|/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    double brightness = 2;
    double scale = 1.0;
    bool invert = false;
    int rotate = 0;
    bool flip_horizontal = false;
    bool flip_vertical = false;
    bool fancy = false;
};
#endif // ASCII_ART_IMGOPTIONS_HPP
