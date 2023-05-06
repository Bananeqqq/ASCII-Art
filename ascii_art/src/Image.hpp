#ifndef ASCII_ART_IMAGE_HPP
#define ASCII_ART_IMAGE_HPP

#include <string>
#include <vector>

class Image {
public:
    Image(unsigned int width, unsigned int height, int num_channels) : width(width), height(height), num_channels(num_channels) {}
    virtual ~Image() = default;
    virtual bool load(const std::string& filename) = 0;

    std::string imgToAscii(float scaleFactor) const;


protected:
    unsigned int width;
    unsigned int height;
    int num_channels;
    std::vector<unsigned char> data;
};


#endif //ASCII_ART_IMAGE_HPP
