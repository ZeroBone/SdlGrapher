#include "Grapher.h"
#include <math.h>
#include <string>
#include <iostream>

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

        SDL_RenderCopy(renderer, texture, nullptr, &rect);

        SDL_DestroyTexture(texture);

        fromX++;

    }

    // vertical line
    SDL_RenderDrawLine(renderer, cx, 0, cx, vHeight);

    int fromY = (int)floor(screenYToMathY(0));
    int toY = (int)floor(screenYToMathY(vHeight));

    while (fromY <= toY) {

        int screenY = mathYToScreenY(fromY);

        SDL_RenderDrawLine(
            renderer,
            cx - 5,
            screenY,
            cx + 5,
            screenY
        );

        // render label

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(
            labelFont,
            std::to_string(fromY).c_str(),
            {0xff, 0xff, 0xff, 0xff}
        );

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        SDL_Rect rect;
        rect.w = surfaceMessage->w;
        rect.h = surfaceMessage->h;
        rect.x = cx + 5; // screenY - rect.w / 2;
        rect.y = screenY;

        SDL_FreeSurface(surfaceMessage);

        SDL_RenderCopy(renderer, texture, nullptr, &rect);

        SDL_DestroyTexture(texture);

        fromY++;

    }

}

void Grapher::init(const char* title, const char* fontFile) {

    App::init(title);

    labelFont = TTF_OpenFont(fontFile, 10);

}

void Grapher::renderGraph() {

    SDL_SetRenderDrawColor(renderer, 0xff, 0xa0, 0xa0, 0xff);

    int startScreenX = 0;

    double startMathX = screenXToMathX(startScreenX++);
    double startMathY = mathFunction(startMathX);

    bool invalidValue = !mathValueValid(startMathY);

    for (; startScreenX < vWidth; startScreenX++) {

        double mathX = screenXToMathX(startScreenX);
        double mathY = mathFunction(mathX);

        if (!mathValueValid(mathY)) {
            invalidValue = true;
            continue;
        }

        if (invalidValue) {
            invalidValue = false;
        }
        else {

            SDL_RenderDrawLine(
                renderer,
                mathXToScreenX(startMathX),
                mathYToScreenY(startMathY),
                mathXToScreenX(mathX),
                mathYToScreenY(mathY)
            );

        }

        startMathX = mathX;
        startMathY = mathY;

    }

}

void Grapher::render(float deltaTime) {

    renderAxes();

    renderGraph();

    SDL_RenderPresent(renderer);

}

void Grapher::handleEvents() {

    while (SDL_PollEvent(&currentEvent)) {

        switch (currentEvent.type) {

            case SDL_QUIT:
                running = false;
                break;

            case SDL_MOUSEWHEEL:

                if (currentEvent.wheel.y > 0) {
                    // Pull up code here!

                    scale += 0.75;

                }
                else if (currentEvent.wheel.y < 0) {
                    // Pull down code here!

                    scale -= 0.75;

                }

                break;

            case SDL_KEYDOWN:

                // std::cout << currentEvent.key.keysym.sym << std::endl;
                // std::cout << currentEvent.key.keysym.scancode << std::endl;

                switch (currentEvent.key.keysym.scancode) {

                    case SDL_SCANCODE_LEFT:
                        cx += 2;
                        break;

                    case SDL_SCANCODE_RIGHT:
                        cx -= 2;
                        break;

                    default:
                        break;

                }

                break;


        }

    }

}