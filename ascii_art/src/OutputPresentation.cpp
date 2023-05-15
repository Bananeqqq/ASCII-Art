#include "OutputPresentation.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <iostream>

bool OutputPresentation::output(const std::vector<std::pair<std::unique_ptr<Image>, Img>> &images, std::string) const{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return false;
    }
    if (TTF_Init() == -1) {
        SDL_Quit();
        return false;
    }

    int windowWidth, windowHeight;
    SDL_Rect displayBounds;
    if (SDL_GetDisplayBounds(0, &displayBounds) != 0){
        windowWidth = 720, windowHeight = 480;
    }
    else {
        windowWidth = std::max(400.0, displayBounds.w*0.6), windowHeight = std::max(400.0, displayBounds.h*0.6);
    }

    SDL_Window* window = SDL_CreateWindow("ASCII-ART", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    TTF_Font* font = TTF_OpenFont("CourierPrime.ttf", 1);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window || !renderer || !font) {
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    std::vector<SDL_Texture*> textures;
    for (const auto& image: images){
        double max_f_size; int font_size = 1;
        if (image.second.fancy) {
            max_f_size = std::min(16000.0 / (image.first->width * image.second.scale), 16000.0 / (image.first->height * image.second.scale));
            font_size = std::max(1.0, std::min(15.0*image.second.scale, max_f_size));
        }
        TTF_SetFontSize(font,font_size);

        SDL_Texture* texture = image.first->createTexture(renderer, font, font_size, image.second.scale);
        if (texture == nullptr) {
            std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            TTF_CloseFont(font);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            return false;
        }
        textures.push_back(texture);
    }

    SDL_SetRenderTarget(renderer, NULL);
    SDL_Texture *onTexture = nullptr, *offTexture = nullptr;
    SDL_Rect autoplay_pos;
    TTF_Font* font2 = TTF_OpenFont("CourierPrime.ttf", 17);
    if (textures.size() > 1) {
        //AutoPlay indicator texture
        SDL_Color textColor = {255, 0, 0, 255};
        SDL_Surface *onSurface = TTF_RenderText_Solid(font2, "Autoplay On", textColor);
        SDL_Surface *offSurface = TTF_RenderText_Solid(font2, "Autoplay Off", textColor);
        onTexture = SDL_CreateTextureFromSurface(renderer, onSurface);
        offTexture = SDL_CreateTextureFromSurface(renderer, offSurface);
        autoplay_pos = {10, 10, onSurface->w, onSurface->h};
        SDL_FreeSurface(onSurface);
        SDL_FreeSurface(offSurface);
    }

    int offsetX = 0, offsetY = 0, current_texture_idx = 0;
    SDL_Texture* texture = textures[0];

    bool mouseDown = false, quit = false, is_autoplay = false; //dat true potom
    Uint32 start_time = SDL_GetTicks();
    Uint32 delay = 3000; //3s

    SDL_Event e;
    double scale = 1.0;

    while (!quit) {
        if (is_autoplay && SDL_GetTicks() - start_time > delay && textures.size() > 1) {
            current_texture_idx = (current_texture_idx + 1) % textures.size();
            texture = textures[current_texture_idx];
            start_time = SDL_GetTicks();
            scale = 1;
            offsetY = 0;
            offsetX = 0;
        }

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_ESCAPE){
                    quit = true;
                }
                else if (e.key.keysym.sym == SDLK_r){
                    offsetX = 0;
                    offsetY = 0;
                    scale = 1;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT){
                    current_texture_idx = (current_texture_idx + 1) % textures.size();
                    scale = 1;
                    offsetY = 0;
                    offsetX = 0;
                    texture = textures[current_texture_idx];
                }
                else if (e.key.keysym.sym == SDLK_LEFT){
                    current_texture_idx = (current_texture_idx - 1 + textures.size()) % textures.size();
                    scale = 1;
                    offsetY = 0;
                    offsetX = 0;
                    texture = textures[current_texture_idx];
                }
                else if (e.key.keysym.sym == SDLK_SPACE){
                    is_autoplay = !is_autoplay;
                }
            }
            else if (e.type == SDL_MOUSEWHEEL){
                if (e.wheel.y > 0){
                    scale *= 1.1;
                }else if (e.wheel.y < 0){
                    scale *= 0.9;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN){
                if (e.button.button == SDL_BUTTON_LEFT){
                    mouseDown = true;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONUP) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = false;
                }
            }
            else if (e.type == SDL_MOUSEMOTION){
                if (mouseDown){
                    offsetX += e.motion.xrel;
                    offsetY += e.motion.yrel;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderSetScale(renderer, scale, scale);

        int textureWidth, textureHeight;
        SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
        double textureAspectRatio = (double)textureWidth / textureHeight;
        int renderW, renderH;
        if (windowWidth/textureAspectRatio <= windowHeight){
            renderW = windowWidth;
            renderH = windowWidth/textureAspectRatio;
        }else {
            renderW = windowHeight*textureAspectRatio;
            renderH = windowHeight;
        }

        SDL_Rect dstRect = {offsetX, offsetY, renderW, renderH};

        SDL_RenderCopy(renderer, texture, NULL, &dstRect);

        if (textures.size() > 1 && scale <= 1.1){
            if (is_autoplay){
                SDL_RenderCopy(renderer, onTexture, NULL, &autoplay_pos);
            }else{
                SDL_RenderCopy(renderer, offTexture, NULL, &autoplay_pos);
            }
        }

        SDL_RenderPresent(renderer);
    }

    for (auto &t_: textures){
        SDL_DestroyTexture(t_);
    }
    SDL_DestroyTexture(onTexture);
    SDL_DestroyTexture(offTexture);
    TTF_CloseFont(font2);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return true;

}