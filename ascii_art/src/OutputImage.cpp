#include "OutputImage.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

bool OutputImage::output(const std::vector<std::pair<std::unique_ptr<Image>, Img>> &images, std::string) const {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return false;
    }

    if (TTF_Init() == -1) {
        SDL_Quit();
        return false;
    }

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int init = IMG_Init(flags);
    if ((init & flags) != flags) {
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    int font_size = 1; //if i'll find a way to calculate width for larger font, then i'll change it
    TTF_Font* font = TTF_OpenFont("CourierPrime.ttf", font_size);

    SDL_Window* window = SDL_CreateWindow("ASCII-ART", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_HIDDEN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    for (const auto& image: images){
        SDL_RenderClear(renderer);
        std::string image_output_name;
        std::string extension = image.second.image_path.substr(image.second.image_path.size() - 4);
        bool is_png = extension == ".png";

        if (is_png) {
            image_output_name = image.second.image_path.substr(0, image.second.image_path.size() - 4) + "_ascii.png";
        }
        else {
            image_output_name = image.second.image_path.substr(0, image.second.image_path.size() - 4) + "_ascii.jpg";
        }


        SDL_Texture* texture = image.first->createTexture(renderer, font, font_size);
        if (!window || !renderer || !font || texture == nullptr) {
            TTF_CloseFont(font);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            return false;
        }

        SDL_SetRenderTarget(renderer, texture);
        int width, height;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
        SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
        SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);


        const char* out = image_output_name.c_str();
        is_png ? IMG_SavePNG(surface, out) : IMG_SaveJPG(surface, out, 100);
        std::cout << "Image saved to " << image_output_name << std::endl;


        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return true;
}