#ifndef ASCII_ART_OUTPUTPRESENTATION_HPP
#define ASCII_ART_OUTPUTPRESENTATION_HPP

#include "Output.hpp"


class OutputPresentation : public Output {
public:
    bool output(const std::vector<std::pair<std::unique_ptr<Image>, Img>> &images, std::string path = "") const override;
};


#endif //ASCII_ART_OUTPUTPRESENTATION_HPP
