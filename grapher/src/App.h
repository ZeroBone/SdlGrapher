#ifndef ZAVU_APP_H
#define ZAVU_APP_H

#include <SDL.h>

class App {

    public:

    App(int vWidth, int vHeight);
    ~App();

    void init(const char* title);

    void handleEvents();

    void render() {

        SDL_RenderPresent(renderer);

    }

    void destroy() {

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();

    }

    void clear() {

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
        SDL_RenderClear(renderer);

    }

    bool isRunning() {
        return running;
    }

    private:
    bool running;
    SDL_Window* window;
    int vWidth, vHeight;
    SDL_Renderer* renderer;
    SDL_Event currentEvent;

};

#endif //ZAVU_APP_H