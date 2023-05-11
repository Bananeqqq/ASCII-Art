#include "OutputFile.hpp"
#include <fstream>
#include <iostream>

bool OutputFile::output(const std::vector<std::pair<std::unique_ptr<Image>, Img>> &images, std::string path) const {
    std::ofstream file(path);

    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return false;
    }

    for (const auto& pair : images) {
        file << pair.first->ascii_image << "\n\n";
    }

    file.close();

    return true;
}