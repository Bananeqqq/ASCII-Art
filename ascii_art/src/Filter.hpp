#ifndef ASCII_ART_FILTER_HPP
#define ASCII_ART_FILTER_HPP
#include "Image.hpp"
#include "ImgOptions.hpp"
#include <memory>

class Filter {
public:
    virtual ~Filter() = default;
    virtual void apply(std::pair<std::unique_ptr<Image>, Img> &image) = 0;

};


#endif //ASCII_ART_FILTER_HPP
