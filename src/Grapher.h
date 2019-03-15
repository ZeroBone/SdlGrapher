#ifndef ZAVU_GRAPHER_H
#define ZAVU_GRAPHER_H

#include <SDL_ttf.h>
#include <limits>
#include <cmath>
#include "App.h"

typedef double (*mathFunction_t)(double);

class Grapher : public App {

    private:

    mathFunction_t mathFunction;
    int cx, cy;
    double scale = 30;
    bool rendering;
    TTF_Font* labelFont;

    public:

    Grapher(mathFunction_t mathFunction) : mathFunction(mathFunction) {}

    ~Grapher();

    void run();
    void init(const char* title, const char* fontFile);
    void onResized();

    private:

    void render() override;
    void renderAxes();
    void renderGraph();
    void adjustForInterval(double intervalStart, double intervalEnd);
    void handleEvents();

    void shouldRerender() {
        rendering = true;
    }

    double screenXToMathX(int screenX) {

        return (screenX - cx) / scale;

    }

    double screenYToMathY(int screenY) {

        return -(screenY - cy) / scale;

    }

    int mathXToScreenX(double mathX) {

        return cx + (int)(mathX * scale);

    }

    int mathYToScreenY(double mathY) {

        return cy - (int)(mathY * scale);

    }

    void handleKeyPressOrRelease() {

        // std::cout << currentEvent.key.keysym.sym << std::endl;
        // std::cout << currentEvent.key.keysym.scancode << std::endl;

        const Uint8* kbStateArray = SDL_GetKeyboardState(nullptr);

        if (kbStateArray[SDL_SCANCODE_UP]) {
            cy += 3;
            shouldRerender();
        }
        else if (kbStateArray[SDL_SCANCODE_DOWN]) {
            cy -= 3;
            shouldRerender();
        }

        if (kbStateArray[SDL_SCANCODE_LEFT]) {
            cx += 3;
            shouldRerender();
        }
        else if (kbStateArray[SDL_SCANCODE_RIGHT]) {
            cx -= 3;
            shouldRerender();
        }

    }

    static bool mathValueValid(double mathValue) {

        return !std::isnan(mathValue) && !std::isinf(mathValue);

        /*return mathValue != std::numeric_limits<double>::quiet_NaN() &&
        mathValue != std::numeric_limits<double>::infinity();*/

    }

};

#endif //ZAVU_GRAPHER_H