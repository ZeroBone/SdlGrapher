#include "Grapher.h"

Grapher::Grapher(int vWidth, int vHeight):App(vWidth, vHeight) {}

void Grapher::run() {

    while (isRunning()) {

        clear();

        handleEvents();

    }

}