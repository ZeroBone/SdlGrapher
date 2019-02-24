#include <limits>
#include "Grapher.h"
#include <math.h>
#include <string>

Grapher::~Grapher() {}

void Grapher::run() {

    while (isRunning()) {

        clear();

        render(1);

        handleEvents();

    }

}

void Grapher::renderAxes() {

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    // horizontal line
    SDL_RenderDrawLine(renderer, 0, cy, vWidth, cy);

    int fromX = (int)floor(screenXToMathX(0));
    int toX = (int)floor(screenXToMathX(vWidth));

    while (fromX <= toX) {

        int screenX = mathXToScreenX(fromX);

        SDL_RenderDrawLine(
            renderer,
            screenX,
            cy - 5,
            screenX,
            cy + 5
        );

        // render label

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(
            labelFont,
            std::to_string(fromX).c_str(),
            {0xff, 0xff, 0xff, 0xff}
        );

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        SDL_Rect rect;
        rect.w = surfaceMessage->w;
        rect.h = surfaceMessage->h;
        rect.x = screenX - rect.w / 2;
        rect.y = cy + 5;

        SDL_FreeSurface(surfaceMessage);

        SDL_RenderCopy(renderer, texture, NULL, &rect);

        SDL_DestroyTexture(texture);

        fromX++;

    }

    // vertical line
    SDL_RenderDrawLine(renderer, cx, 0, cx, vHeight);

}

void Grapher::init(const char* title, const char* fontFile) {

    App::init(title);

    labelFont = TTF_OpenFont(fontFile, 20);

}

void Grapher::renderGraph() {

    SDL_SetRenderDrawColor(renderer, 0xff, 0xa0, 0xa0, 0xff);

    int startScreenX = 0;

    double startMathX = screenXToMathX(startScreenX++);
    double startMathY = mathFunction(startMathX);

    for (; startScreenX < vWidth; startScreenX++) {

        double mathX = screenXToMathX(startScreenX);
        double mathY = mathFunction(mathX);

        if (mathY == std::numeric_limits<double>::quiet_NaN()) {
            continue;
        }

        SDL_RenderDrawLine(
            renderer,
            mathXToScreenX(startMathX),
            mathYToScreenY(startMathY),
            mathXToScreenX(mathX),
            mathYToScreenY(mathY)
        );

        startMathX = mathX;
        startMathY = mathY;

    }

}

void Grapher::render(float deltaTime) {

    renderAxes();

    renderGraph();

    scale-=0.002;

    SDL_RenderPresent(renderer);

}