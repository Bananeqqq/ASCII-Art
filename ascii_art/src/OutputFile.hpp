#ifndef ASCII_ART_OUTPUTFILE_HPP
#define ASCII_ART_OUTPUTFILE_HPP

#include "Output.hpp"

class OutputFile : public Output {
    bool output(const std::vector<std::pair<std::unique_ptr<Image>, Img>> &images, std::string path = "") const override;
};


#endif //ASCII_ART_OUTPUTFILE_HPP
