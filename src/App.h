#ifndef ZAVU_APP_H
#define ZAVU_APP_H

#include <SDL.h>
#include <iostream>

class App {

    protected:

    bool running;
    SDL_Window* window;

    SDL_Renderer* renderer;
    SDL_Event currentEvent;
    int vWidth, vHeight;

    public:

    App();
    ~App();

    virtual void init(const char* title);

    virtual void render() {

        SDL_RenderPresent(renderer);

    }

    virtual void onResized() {

        // std::cout << "resized" << std::endl;

        SDL_GetRendererOutputSize(renderer, &vWidth, &vHeight);

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