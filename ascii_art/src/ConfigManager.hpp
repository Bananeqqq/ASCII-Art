#ifndef ASCII_ART_CONFIGMANAGER_HPP
#define ASCII_ART_CONFIGMANAGER_HPP

#include <string>
#include <unordered_map>
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
    bool parseConfig(const std::string &cfg_path, Img &img);
    std::vector<Img> images;
    std::vector<std::string> args;
    std::string output_file_path;
    bool output_console;
    bool output_screen;
    bool output_file;
    std::vector<size_t> image_positions;
    bool is_config_for_all;
    std::string global_cfg;

};


#endif //ASCII_ART_CONFIGMANAGER_HPP
