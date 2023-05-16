#ifndef ASCII_ART_FILTERROTATE_HPP
#define ASCII_ART_FILTERROTATE_HPP
#include "Filter.hpp"

class FilterRotate : public Filter {
public:
    void apply(std::pair<std::unique_ptr<Image>, Img> &image) override;
};


#endif //ASCII_ART_FILTERROTATE_HPP
