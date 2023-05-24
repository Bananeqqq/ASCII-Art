#ifndef ASCII_ART_OUTPUT_HPP
#define ASCII_ART_OUTPUT_HPP
#include "Image.hpp"
#include <vector>
#include <memory>
#include "ImgOptions.hpp"

/**
 * @brief Abstract base class for different output types
 *
 * @details This class is used to output the images to the console, to a file or to a presentation.
 * Derived classes are OutputFile, OutputImage and OutputPresentation and they must implement the output method
 */
class Output
{
public:
    virtual ~Output() = default;

    /**
     * @brief Pure virtual method for outputting the images
     * @param images Vector of pairs of images and ImgOptions which contain the configuration and data for the images
     * @param path Optional parameter for the path to the file to be outputted. Default is empty string
     * @return True if output was successful, false otherwise
     */
    virtual bool output(const std::vector<std::pair<std::unique_ptr<Image>, Img>> &images, std::string path = "") const = 0;
    
    /**
     * @brief Path to the font used for the presentation and image output
     * 
     */
    const char* FONT_PATH = "assets/CourierPrime.ttf";
};

#endif // ASCII_ART_OUTPUT_HPP
