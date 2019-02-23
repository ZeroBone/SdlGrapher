#include <iostream>
#include "src/Grapher.h"
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

    Grapher* grapher = new Grapher(640, 480);

    grapher->init("Grapher");

    grapher->run();

    grapher->destroy();

    return 0;

}