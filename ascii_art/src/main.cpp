#include <iostream>
#include <memory>
#include "ImagePNG.hpp"

#include <string>



int main() {

    std::unique_ptr<Image> img;
    img = std::unique_ptr<Image>(new ImagePNG());
    const float scale = 1;
    if (!img->load("/mnt/c/Users/danki/OneDrive/Plocha/CVUT/2.semestr/PA2/Git/zemladan/ascii_art/pics/tiger1.png")) return 1;


    return 0;
}
