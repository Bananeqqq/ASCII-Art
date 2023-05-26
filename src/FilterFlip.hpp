#ifndef ASCII_ART_FILTERFLIP_HPP
#define ASCII_ART_FILTERFLIP_HPP
#include "Filter.hpp"

/**
 * @brief Filter for flipping image horizontally or vertically
 */
class FilterFlip : public Filter
{
public:
    void apply(std::pair<std::unique_ptr<Image>, Img> &image) override;
};

#endif // ASCII_ART_FILTERFLIP_HPP
