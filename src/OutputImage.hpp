#ifndef ASCII_ART_OUTPUTIMAGE_HPP
#define ASCII_ART_OUTPUTIMAGE_HPP

#include "Output.hpp"

/**
 * @brief Class for outputting the images to a png file
 */
class OutputImage : public Output
{
public:
    bool output(const std::vector<std::pair<std::unique_ptr<Image>, Img>> &images, std::string path = "") const override;
};

#endif // ASCII_ART_OUTPUTIMAGE_HPP
