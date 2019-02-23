#ifndef ZAVU_GRAPHER_H
#define ZAVU_GRAPHER_H

#include "App.h"

class Grapher : public App {

    public:

    Grapher(int vWidth, int vHeight);
    ~Grapher();

    void run();

};

#endif //ZAVU_GRAPHER_H