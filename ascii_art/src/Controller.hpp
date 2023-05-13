#ifndef ASCII_ART_CONTROLLER_HPP
#define ASCII_ART_CONTROLLER_HPP
#include <string>
#include <memory>
#include "Filter.hpp"
#include "ConfigManager.hpp"

class Controller {
public:
    Controller(int argc, char *argv[]);
    void run();
    bool loadImages();
    void applyFilters();
    bool convertToAscii();
    void outputImages();

private:
    ConfigManager config;
    std::vector<std::pair<std::unique_ptr<Image>, Img>> images;
};


#endif //ASCII_ART_CONTROLLER_HPP
