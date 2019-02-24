#ifndef ZAVU_APP_H
#define ZAVU_APP_H

#include <SDL.h>

class App {

    private:

    bool running;
    SDL_Window* window;

    protected:

    SDL_Renderer* renderer;
    SDL_Event currentEvent;
    int vWidth, vHeight;

    public:

    App(int vWidth, int vHeight);
    ~App();

    void init(const char* title);

    void handleEvents();

    virtual void render(float deltaTime) {

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

};

#endif //ZAVU_APP_H