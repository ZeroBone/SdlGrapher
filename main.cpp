#include <iostream>
#include "src/Grapher.h"
#include <math.h>
#include <SDL.h>

#include <limits>

double mathF(double x) {

    // return 1 / x;

    /*if (x < 0.001) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    return log(x);*/

    // return sin(x);
    // return cos(x);

    return (3.0 * sin(x / 4.0)) - (2.0 / sin(2.0 * x));

}

int main(int argc, char* argv[]) {

    Grapher* grapher = new Grapher(mathF);

    grapher->init("Grapher", "arial.ttf");

    grapher->run();

    grapher->destroy();

    delete grapher;

    return 0;

}