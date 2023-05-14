#include "Image.hpp"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <algorithm>

void Image::imgToAscii(const double scaleFactor, const std::string charset, double brightness) {
    int scaledWidth = width * scaleFactor;
    int scaledHeight = height * scaleFactor;

    if (data.size() < width*height){
        std::cout << "Image: Error while converting to ascii" << std::endl;
        return;
    }

    for (int y = 0; y < scaledHeight; ++y) {
        for (int x = 0; x < scaledWidth; ++x) {
            int scaledX = x / scaleFactor;
            int scaledY = y / scaleFactor;
            int index = scaledY * width + scaledX;
            auto pixel = data[index];

            if (brightness < 0){
                brightness = 0;
            }

            double gray_level = pow(pixel / 255.0, brightness);
            int idx = (double)(gray_level * (charset.length() - 1));
            ascii_image += charset[idx];
        }
        ascii_image += '\n';
    }
}


SDL_Texture* Image::createTexture(SDL_Renderer* renderer, TTF_Font* font, int font_size) const {
    SDL_Color textColor = {255, 255, 255, 255};

    int full_width = width * font_size;
    int full_height = height * font_size;

    std::vector<SDL_Surface*> surfaces;
    const char* text = ascii_image.c_str();
    std::stringstream ss(text);
    std::string line;
    while (std::getline(ss, line)) {
        SDL_Surface* surface = TTF_RenderText_Blended(font, line.c_str(), textColor);

        if (surface == nullptr){
            std::cout << "Error creating text surface: " << TTF_GetError() << std::endl;
        }
        surfaces.push_back(surface);
    }

    SDL_Texture* full_image = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, full_width, full_height);
    if (full_image == nullptr){
        std::cout << "Error creating full image texture: " << SDL_GetError() << std::endl;
    }


    SDL_SetRenderTarget(renderer, full_image);
    SDL_SetTextureBlendMode(full_image, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(renderer);

    int i = 0;
    double multiply_factor = (double)full_width/ surfaces[0]->w;
    for (SDL_Surface* surface : surfaces){
        SDL_Texture *lineTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect dstRect = {0, i*font_size, static_cast<int>(surface->w*multiply_factor), surface->h};
        i++;

        SDL_RenderCopy(renderer, lineTexture, NULL, &dstRect);
        SDL_FreeSurface(surface);
//        SDL_DestroyTexture(lineTexture);
    }

    return full_image;
}