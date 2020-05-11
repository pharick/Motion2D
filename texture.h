//
// Created by Артем Форкунов on 10.05.2020.
//

#ifndef MOTION1D_TEXTURE_H
#define MOTION1D_TEXTURE_H

#include <string>
#include "SDL.h"

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);

#endif //MOTION1D_TEXTURE_H
