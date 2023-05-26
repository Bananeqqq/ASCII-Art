#ifndef ASCII_ART_CONTROLLER_HPP
#define ASCII_ART_CONTROLLER_HPP
#include <string>
#include <memory>
#include "Filter.hpp"
#include "ConfigManager.hpp"

/**
 * @brief Controller class that handles the flow of the program
 */
class Controller
{
public:
    /**
     * @brief Construct a new Controller object and initialize the ConfigManager
     * @param argc The number of arguments passed to the program
     * @param argv The arguments passed to the program
     */
    Controller(int argc, char *argv[]);

    /**
     * @brief Run the program - load images, apply filters, convert to ascii, and output images
     */
    void run();

    /**
     * @brief Load images from the vector of image configuration we initialized in the ConfigManager
     * @return true if image was loaded successfully, false otherwise
     */
    bool loadImages();

    /**
     * @brief Apply filters to the images
     */
    void applyFilters();

    /**
     * @brief Convert images to ascii
     */
    void convertToAscii();

    /**
     * @brief Output images the way the user specified in the command line
     */
    void outputImages();

private:
    /**
     * @brief ConfigManager object that handles the configuration of the program
     */
    ConfigManager config;

    /**
     * @brief Vector of pairs of unique_ptr to Image and Img object, so we have the image data and its configuration
     */
    std::vector<std::pair<std::unique_ptr<Image>, Img>> images;
};

#endif // ASCII_ART_CONTROLLER_HPP
