#ifndef ASCII_ART_FILTER_HPP
#define ASCII_ART_FILTER_HPP
#include "Image.hpp"
#include "ImgOptions.hpp"
#include <memory>

/**
 * @brief Abstract class for filters
 */
class Filter
{
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Filter() = default;

    /**
     * @brief Applies filter to image
     * @param image Image to apply filter to
     */
    virtual void apply(std::pair<std::unique_ptr<Image>, Img> &image) = 0;
};

#endif // ASCII_ART_FILTER_HPP
