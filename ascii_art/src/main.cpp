#include <iostream>
#include <memory>
#include "ImagePNG.hpp"
#include "ImageJPG.hpp"
#include <string>



int main() {

    std::unique_ptr<Image> img;
    std::unique_ptr<Image> imgJ;
    img = std::unique_ptr<Image>(new ImagePNG());
    imgJ = std::unique_ptr<Image>(new ImageJPG());
    const float scale = 0.1;
    std::string ascii_image;

    if (!imgJ->load("/mnt/c/Users/danki/OneDrive/Plocha/CVUT/2.semestr/PA2/Git/zemladan/ascii_art/pics/cats/tiger2.jpg")) return 1;
    std::cout << "Jpg:" << std::endl;
    ascii_image = imgJ->imgToAscii(scale);
//    std::cout << ascii_image << std::endl;


    if (!img->load("/mnt/c/Users/danki/OneDrive/Plocha/CVUT/2.semestr/PA2/Git/zemladan/ascii_art/pics/cats/tiger2.png")) return 1;
    std::cout << "Png:" << std::endl;
    ascii_image = img->imgToAscii(scale);
//    std::cout << ascii_image << std::endl;


    return 0;
}
