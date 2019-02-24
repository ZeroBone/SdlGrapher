#include <iostream>
#include "src/Grapher.h"
#include <math.h>
#include <SDL.h>
#include "SDL_ttf.h"
#include <limits>

double mathF(double x) {

    return x;

}

int main(int argc, char* argv[]) {

    Grapher* grapher = new Grapher(640, 480, mathF);

    grapher->init("Grapher");

    grapher->run();

    grapher->destroy();

    delete grapher;

    return 0;

}