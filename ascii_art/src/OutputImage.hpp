#ifndef ASCII_ART_OUTPUTIMAGE_HPP
#define ASCII_ART_OUTPUTIMAGE_HPP

#include "Output.hpp"

class OutputImage : public Output {
public:
    bool output(const std::vector<std::pair<std::unique_ptr<Image>, Img>> &images, std::string path = "") const override;

};


#endif //ASCII_ART_OUTPUTIMAGE_HPP
