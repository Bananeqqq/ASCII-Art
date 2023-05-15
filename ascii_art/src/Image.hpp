#ifndef ASCII_ART_IMAGE_HPP
#define ASCII_ART_IMAGE_HPP

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Image {
public:
    Image(unsigned int width, unsigned int height) : width(width), height(height) {
        ascii_image = "";
    }
    virtual ~Image() = default;
    virtual bool load(const std::string& filename, bool inverted) = 0;

    void imgToAscii(const double scaleFactor, const std::string charset, double brightness);
    SDL_Texture* createTexture(SDL_Renderer* renderer, TTF_Font* font, int font_size, double scale) const;

    unsigned int width;
    unsigned int height;
    std::vector<unsigned char> data;
    std::string ascii_image;
};


#endif //ASCII_ART_IMAGE_HPP
