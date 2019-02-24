#include "App.h"
#include <SDL_ttf.h>

App::App(int vWidth, int vHeight): vWidth(vWidth), vHeight(vHeight) {}
App::~App() {}

void App::init(const char* title) {

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        running = false;
        return;
    }

    // window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, vWidth, vHeight, SDL_WINDOW_OPENGL);

    if (!window) {
        running = false;
        return;
    }

    // renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        running = false;
        return;
    }

    if (TTF_Init() < 0) {
        running = false;
        return;
    }

    running = true;

}

void App::handleEvents() {

    while (SDL_PollEvent(&currentEvent)) {

        switch (currentEvent.type) {

            case SDL_QUIT:
                running = false;
                break;

        }

    }

}