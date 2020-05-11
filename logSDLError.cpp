//
// Created by Артем Форкунов on 10.05.2020.
//

#include "logSDLError.h"

#include "SDL.h"

void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}
