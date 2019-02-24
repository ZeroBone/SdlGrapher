#ifndef ZAVU_GRAPHER_H
#define ZAVU_GRAPHER_H

#include <SDL_ttf.h>
#include "App.h"

typedef double (*mathFunction_t)(double);

class Grapher : public App {

    private:

    mathFunction_t mathFunction;
    int cx = 320, cy = 240;
    double scale = 50;
    TTF_Font* labelFont;

    public:

    Grapher(int vWidth, int vHeight, mathFunction_t mathFunction) : mathFunction(mathFunction), App(vWidth, vHeight) {}

    ~Grapher();

    void run();
    void init(const char* title, const char* fontFile);

    private:

    void render(float deltaTime) override;
    void renderAxes();
    void renderGraph();

    double screenXToMathX(int screenX) {

        return (screenX - cx) / scale;

    }

    int mathXToScreenX(double mathX) {

        return cx + (int)(mathX * scale);

    }

    int mathYToScreenY(double mathY) {

        return cy - (int)(mathY * scale);

    }

};

#endif //ZAVU_GRAPHER_H