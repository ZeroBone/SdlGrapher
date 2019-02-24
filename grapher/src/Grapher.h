#ifndef ZAVU_GRAPHER_H
#define ZAVU_GRAPHER_H

#include "App.h"

typedef double (*mathFunction_t)(double);

class Grapher : public App {

    private:

    mathFunction_t mathFunction;
    int cx = 320, cy = 240;

    public:

    Grapher(int vWidth, int vHeight, mathFunction_t mathFunction) : mathFunction(mathFunction), App(vWidth, vHeight) {}

    ~Grapher();

    void run();

    private:

    void render(float deltaTime) override;
    void renderAxes();
    void renderGraph();

    double screenXToMathX(int screenX) {

        return screenX - cx;

    }

    int mathXToScreenX(double mathX) {

        return cx + mathX;

    }

    int mathYToScreenY(double mathY) {

        return cy - mathY;

    }

};

#endif //ZAVU_GRAPHER_H