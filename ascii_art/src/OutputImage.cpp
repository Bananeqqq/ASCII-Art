#include "OutputImage.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

bool OutputImage::output(const std::vector<std::pair<std::unique_ptr<Image>, Img>> &images, std::string) const
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return false;
    }

    if (TTF_Init() == -1)
    {
        SDL_Quit();
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    SDL_Window *window = SDL_CreateWindow("ASCII-ART", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_HIDDEN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font *font = TTF_OpenFont(FONT_PATH, 1);

    for (const auto &image : images)
    {
        double max_f_size;
        int font_size = 1;
        if (image.second.fancy)
        {
            max_f_size = std::min(16000.0 / (image.first->width * image.second.scale), 16000.0 / (image.first->height * image.second.scale));
            font_size = std::max(1.0, std::min(15.0 * image.second.scale, max_f_size));
        }

        // Due to old ProgTest library version, I am unable to use TTF_SetFontSize
        TTF_CloseFont(font);
        font = TTF_OpenFont(FONT_PATH, font_size);

        if (!window || !renderer || !font)
        {
            if (font)
            {
                TTF_CloseFont(font);
            }

            if (renderer)
            {
                SDL_DestroyRenderer(renderer);
            }

            if (window)
            {
                SDL_DestroyWindow(window);
            }

            IMG_Quit();
            TTF_Quit();
            SDL_Quit();
            return false;
        }

        SDL_RenderClear(renderer);
        SDL_Texture *texture = image.first->createTexture(renderer, font, font_size, image.second.scale);

        if (!texture)
        {
            TTF_CloseFont(font);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            TTF_Quit();
            SDL_Quit();
            return false;
        }

        SDL_SetRenderTarget(renderer, texture);
        int width, height;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
        SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

        if (!surface || SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch) != 0)
        {
            TTF_CloseFont(font);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            TTF_Quit();
            SDL_Quit();
            return false;
        }

        std::string image_output_name = image.second.image_path.substr(0, image.second.image_path.size() - 4) + "_ascii.png";
        const char *out = image_output_name.c_str();

        if (IMG_SavePNG(surface, out) != 0)
        {
            TTF_CloseFont(font);
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            TTF_Quit();
            SDL_Quit();
            return false;
        }
        std::cout << "Image saved to " << image_output_name << std::endl;

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return true;
}