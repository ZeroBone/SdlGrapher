#include <iostream>
#include "src/Grapher.h"
#include <math.h>
#include <SDL.h>

#include <limits>

double mathF(double x) {

    // return sin(x);

    return cos(x);

}

int main(int argc, char* argv[]) {

    Grapher* grapher = new Grapher(640, 480, mathF);

    grapher->init("Grapher", "arial.ttf");

    grapher->run();

    grapher->destroy();

    delete grapher;

    return 0;

}