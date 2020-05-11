#include <iostream>
#include <vector>
#include "SDL.h"

#include "cleanup.h"
#include "logSDLError.h"
#include "texture.h"

struct point {
    double x;
    double y;
};

int main(int argc, char **argv) {
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Motion2D", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logSDLError(std::cout, "SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError(std::cout, "SDL_CreateRenderer");
        cleanup(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *ball = loadTexture("resources/ball.bmp", renderer);

    if (ball == nullptr) {
        cleanup(ball, renderer, window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    const double G = 9.8; // m/s^2

    double x = 10; // m
    double y = 100; // m

    double time = 0; // s
    double speedX = 50; // m/s
    double speedY = -20; // m/s

    std::vector<point> points = {};

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        std::cout << "Time: " << time << "s | "
                  << "SpeedX: " << speedX << "m/s | "
                  << "SpeedY: " << speedY << "m/s | "
                  << "x: " << x << "m | "
                  << "y: " << y << "m"
                  << std::endl;

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        points.push_back({x, y});

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        for (point p : points) {
            SDL_Rect dot = {(int) p.x, (int) p.y, 2, 2};
            SDL_RenderFillRect(renderer, &dot);
        }

        int ballW, ballH;
        SDL_QueryTexture(ball, NULL, NULL, &ballW, &ballH);
        renderTexture(ball, renderer, (int) x - ballW / 2, (int) y - ballH / 2);

        x += speedX / 20;
        y += speedY / 20;

        time += 0.050;
        speedY += G / 20;

        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }

    cleanup(ball, renderer, window);

    SDL_Quit();
    return 0;
}
