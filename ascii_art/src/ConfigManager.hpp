#ifndef ASCII_ART_CONFIGMANAGER_HPP
#define ASCII_ART_CONFIGMANAGER_HPP

#include <string>
#include <vector>
#include "ImgOptions.hpp"


class ConfigManager {
public:
    ConfigManager(int agrc, char *argv[]);
    void parseCommandLine();

    std::string getOutputPath() const;
    std::vector<Img> getImages() const;
    std::string getOutputType() const;

private:
    bool parseConfigFile(const std::string &cfg_path, Img &img);
    bool checkArgs(Img& current_config, size_t min, size_t max);
    std::vector<Img> images;
    std::vector<std::string> args;
    std::string output_file_path;
    bool output_console;
    bool output_screen;
    bool output_file;
    bool output_image;
    std::vector<size_t> image_positions;

};


#endif //ASCII_ART_CONFIGMANAGER_HPP
