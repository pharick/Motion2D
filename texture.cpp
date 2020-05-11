//
// Created by Артем Форкунов on 10.05.2020.
//

#include "texture.h"

#include "logSDLError.h"

SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *renderer) {
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

    if (loadedImage != nullptr) {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);

        if (texture == nullptr) {
            logSDLError(std::cout, "CreateTextureFromSurface");
        }
    } else {
        logSDLError(std::cout, "LoadBMP");
    }

    return texture;
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y) {
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
    SDL_RenderCopy(renderer, texture, NULL, &destination);
}
