#include "App.h"
#include <SDL_ttf.h>

App::App() = default;
App::~App() = default;

void App::init(const char* title) {

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        running = false;
        return;
    }

    // window
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        running = false;
        return;
    }

    // SDL_GetWindowSize(window, &vWidth, &vHeight);

    // renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        running = false;
        return;
    }

    SDL_GetRendererOutputSize(renderer, &vWidth, &vHeight);

    if (TTF_Init() < 0) {
        running = false;
        return;
    }

    running = true;

}