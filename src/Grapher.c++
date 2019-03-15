#include "Grapher.h"
#include <math.h>
#include <string>
#include <iostream>

Grapher::~Grapher() = default;

void Grapher::adjustForInterval(double intervalStart, double intervalEnd) {

    double distance = intervalEnd - intervalStart;

    cx = (int)(-intervalStart * vWidth / distance);

    scale = vWidth / distance;

}

void Grapher::run() {

    while (isRunning()) {

        if (rendering) {

            clear();

            render();

            rendering = false;

        }

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

    // int fromY = (int)floor(screenYToMathY(0));
    // int toY = (int)ceil(screenYToMathY(vHeight));
    int fromY = (int)floor(screenYToMathY(vHeight));
    int toY = (int)ceil(screenYToMathY(0));

    // std::cout << fromY << " " << toY << std::endl;

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

    cx = vWidth / 2;
    cy = vHeight / 2;

    rendering = true;

    labelFont = TTF_OpenFont(fontFile, 10);

}

void Grapher::onResized() {

    App::onResized();

    cx = vWidth / 2;
    cy = vHeight / 2;

    shouldRerender();

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
            // std::cout << "Invalid value" << std::endl;
            invalidValue = true;
            continue;
        }

        if (invalidValue) {
            invalidValue = false;
        }
        else if (fabs(startMathY - mathY) > 40.) {}
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

void Grapher::render() {

    // std::cout << "W: " << vWidth << " H: " << vHeight << std::endl;

    renderAxes();

    renderGraph();

    SDL_RenderPresent(renderer);

}

void Grapher::handleEvents() {

    while (SDL_PollEvent(&currentEvent)) {

        switch (currentEvent.type) {

            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                onResized();
                break;

            case SDL_WINDOWEVENT:

                if (currentEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
                    onResized();
                }

                break;

            case SDL_QUIT:
                running = false;
                break;

            case SDL_MOUSEWHEEL:

                if (currentEvent.wheel.y > 0) {

                    scale += 0.75;
                    shouldRerender();

                }
                else if (currentEvent.wheel.y < 0) {

                    scale -= 0.75;
                    shouldRerender();

                }

                break;

            case SDL_KEYDOWN:

                switch (currentEvent.key.keysym.scancode) {

                    /*case SDL_SCANCODE_UP:
                        cy += 3;
                        shouldRerender();
                        break;

                    case SDL_SCANCODE_DOWN:
                        cy -= 3;
                        shouldRerender();
                        break;

                    case SDL_SCANCODE_LEFT:
                        cx += 3;
                        shouldRerender();
                        break;

                    case SDL_SCANCODE_RIGHT:
                        cx -= 3;
                        shouldRerender();
                        break;*/

                    case SDL_SCANCODE_I:

                        double start;
                        double end;

                        std::cout << "Enter interval beginning:" << std::endl;
                        std::cin >> start;
                        std::cout << "Enter interval end:" << std::endl;
                        std::cin >> end;

                        if (start >= end) {
                            std::cout << "Invalid interval." << std::endl;
                            break;
                        }

                        adjustForInterval(start, end);

                        shouldRerender();

                        break;

                    case SDL_SCANCODE_ESCAPE:

                        running = false;

                        break;

                    default:

                        handleKeyPressOrRelease();

                        break;

                }

                break;

            case SDL_KEYUP:

                handleKeyPressOrRelease();

            default:
                break;

        }

    }

}