#include "Grapher.h"

Grapher::~Grapher() {}

void Grapher::run() {

    while (isRunning()) {

        clear();

        render(1);

        handleEvents();

    }

}

void Grapher::renderAxes() {

    SDL_SetRenderDrawColor(renderer, 0xf0, 0xf0, 0xf0, 0xff);

    // horizontal line
    SDL_RenderDrawLine(renderer, 0, cy, vWidth, cy);

    SDL_RenderDrawLine(renderer, cx, 0, cx, vHeight);

}

void Grapher::renderGraph() {

    SDL_SetRenderDrawColor(renderer, 0xff, 0xa0, 0xa0, 0xff);

    int startScreenX = 0;

    double startMathX = screenXToMathX(startScreenX);
    double startMathY = mathFunction(startMathX);

    for (; startScreenX < vWidth; startScreenX++) {

        double mathX = screenXToMathX(startScreenX);
        double mathY = mathFunction(mathX);

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

    SDL_RenderPresent(renderer);

}