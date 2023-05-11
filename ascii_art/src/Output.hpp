#ifndef ASCII_ART_OUTPUT_HPP
#define ASCII_ART_OUTPUT_HPP
#include "Image.hpp"
#include <vector>
#include <memory>
#include "ImgOptions.hpp"

class Output {
public:
    virtual ~Output() = default;
    virtual bool output(const std::vector<std::pair<std::unique_ptr<Image>, Img>> &images, std::string path = "") const = 0;
};


#endif //ASCII_ART_OUTPUT_HPP
