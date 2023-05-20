#ifndef ASCII_ART_CONFIGMANAGER_HPP
#define ASCII_ART_CONFIGMANAGER_HPP

#include <string>
#include <vector>
#include "ImgOptions.hpp"

/**
 * @brief Class for managing the configuration of the program
 */

class ConfigManager {
public:
    /**
     * @brief Constructor for the ConfigManager class, saves the command line arguments and meanwhile saves the index of the images and parses output option
     *
     * @param agrc number of command line arguments
     * @param argv command line arguments
     */
    ConfigManager(int agrc, char *argv[]);


    /**
     * @brief Parses the command line arguments
     */
    void parseCommandLine();


    /**
     * @brief Get file output path
     * @return std::string output path
     */
    std::string getOutputPath() const;


    /**
     * @brief get vector of configurations for images
     * @return std::vector<Img> vector of configurations for images
     */
    std::vector<Img> getImages() const;


    /**
     * @brief get output option type
     * @return std::string output option type
     */
    std::string getOutputType() const;

private:

    /**
     * @brief Parses the config file
     * @param cfg_path path to the config file
     * @param img Img object to store the parsed configurations
     * @return true if the config file was parsed successfully
     */
    bool parseConfigFile(const std::string &cfg_path, Img &img);


    /**
     * @brief Parses the command line arguments within bounds [min, max] for the current image.
     * Uses the image index [min] we saved in the constructor so we can parse the arguments to the correct image ([max] is the next image index).
     *
     * @param current_config Img object to store the parsed configurations
     * @param min index of the first argument for the current image
     * @param max index of the last argument for the current image
     */
    void checkArgs(Img& current_config, size_t min, size_t max);


    /**
     * @brief stores the configuration of images
     */
    std::vector<Img> images;

    /**
     * @brief stores the command line arguments
     */
    std::vector<std::string> args;

    /**
     * @brief output file path if the output option is file
     */
    std::string output_file_path;

    /**
     * @brief true if the output option is console
     */
    bool output_console;

    /**
     * @brief true if the output option is screen (window)
     */
    bool output_screen;

    /**
     * @brief true if the output option is file
     */
    bool output_file;

    /**
     * @brief true if the output option is to save image as png
     */
    bool output_image;


    /**
     * @brief stores the index of the images in the command line arguments
     */
    std::vector<size_t> image_positions;

};


#endif //ASCII_ART_CONFIGMANAGER_HPP
