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
    TTF_Font* labelFont;

    public:

    Grapher(int vWidth, int vHeight, mathFunction_t mathFunction) :
        mathFunction(mathFunction),
        cx(vWidth / 2),
        cy(vHeight / 2),
        App(vWidth, vHeight) {}

    ~Grapher();

    void run();
    void init(const char* title, const char* fontFile);

    private:

    void render(float deltaTime) override;
    void renderAxes();
    void renderGraph();
    void adjustForInterval(double intervalStart, double intervalEnd);
    void handleEvents();

    double screenXToMathX(int screenX) {

        return (screenX - cx) / scale;

    }

    double screenYToMathY(int screenY) {

        return (screenY - cy) / scale;

    }

    int mathXToScreenX(double mathX) {

        return cx + (int)(mathX * scale);

    }

    int mathYToScreenY(double mathY) {

        return cy - (int)(mathY * scale);

    }

    static bool mathValueValid(double mathValue) {

        return !std::isnan(mathValue) && !std::isinf(mathValue);

        /*return mathValue != std::numeric_limits<double>::quiet_NaN() &&
        mathValue != std::numeric_limits<double>::infinity();*/

    }

};

#endif //ZAVU_GRAPHER_H