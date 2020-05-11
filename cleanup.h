//
// Created by Артем Форкунов on 10.05.2020.
//

#ifndef MOTION1D_CLEANUP_H
#define MOTION1D_CLEANUP_H

#include <utility>
#include "SDL.h"

template<typename T, typename... Args>
void cleanup(T *t, Args &&... args) {
    cleanup(t);
    cleanup(std::forward<Args>(args)...);
}

template<>
void cleanup<SDL_Window>(SDL_Window *window) {
    if (window) {
        SDL_DestroyWindow(window);
    }
}

template<>
void cleanup<SDL_Renderer>(SDL_Renderer *renderer) {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
}

template<>
void cleanup<SDL_Texture>(SDL_Texture *texture) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

template<>
void cleanup<SDL_Surface>(SDL_Surface *surface) {
    if (surface) {
        SDL_FreeSurface(surface);
    }
}

#endif //MOTION1D_CLEANUP_H
