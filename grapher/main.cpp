#include <iostream>
#include <math.h>
#include <SDL.h>
#include "SDL_ttf.h"
#include <limits>

#define V_WIDTH 640
#define V_HEIGTH 480

double mathFunction(double x) {

    // if (x >= -10.5 && x <= -9.5) return x + 10.;

    return sin(x) * 30;

    /*if (x < 0) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    return sqrt(x);*/

}

int main(int argc, char* argv[]) {

    SDL_Window* window;

    SDL_Init(SDL_INIT_VIDEO);

    // window
    window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, V_WIDTH, V_HEIGTH, SDL_WINDOW_OPENGL);

    // renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    // events
    SDL_Event event;

    // loop
    SDL_bool finished = SDL_FALSE;

    // font
    TTF_Font* font = TTF_OpenFont("sm.ttf", 24);

    double epsilon = 0.01;
    double fromX = -10;
    double toX = 10;
    double screenToMathRatio = (fabs(fromX) + fabs(toX)) / V_WIDTH;

    while (!finished) {

        // clear everything
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xf0, 0xf0, 0xf0, 0xff);

        SDL_RenderDrawLine(renderer, 0, V_HEIGTH / 2, V_WIDTH, V_HEIGTH / 2);
        SDL_RenderDrawLine(renderer, V_WIDTH / 2, 0, V_WIDTH / 2, V_HEIGTH);
        // SDL_RenderDrawPoint(renderer, 110, 110);

        SDL_SetRenderDrawColor(renderer, 0xa0, 0xff, 0xa0, 0xff);

        double startX = 0, startY = 0;
        double currentX, currentY;

        while (startX < V_WIDTH) {

            currentX = startX + epsilon;
            currentY = mathFunction((currentX - (V_WIDTH / 2)) * screenToMathRatio);

            if (std::numeric_limits<double>::quiet_NaN() == currentY) {
                continue;
            }

            SDL_RenderDrawLine(
                renderer,
                startX,
                V_HEIGTH / 2 - startY,
                currentX,
                V_HEIGTH / 2 - currentY
            );

            startX = currentX;
            startY = currentY;

        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xa0, 0xa0, 0xff);

        for (double i = fromX; i < toX; i++) {

            int x = (V_WIDTH / 2) + (i / screenToMathRatio);

            SDL_RenderDrawLine(
                renderer,
                x,
                (V_HEIGTH / 2) - 5,
                x,
                (V_HEIGTH / 2) + 5
            );

            SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "put your text here", White);



        }

//        SDL_Rect rect;
//        rect.x = rect.y = 100;
//        rect.w = rect.h = 300;
//
//        SDL_SetRenderDrawColor(renderer, 0xff, 0, 0, 0xff);
//
//        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);

        // SDL_Delay(3000);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                finished = SDL_TRUE;
            }
        }

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;

}