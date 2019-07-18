#ifndef SDL_INTERFACE_H
#define SDL_INTERFACE_H

#include "interface.hpp"
#include <SDL2/SDL.h>

class SDL : public Interface{
    public:
        static key_callback keyHook;

        SDL();
        SDL(SDL const & obj);
        ~SDL();

        int open_window(int width, int height);
        void drawBorder();
        void updateView();

        void bindKeyCallback( const key_callback);
        bool closing();

        std::string getName();
    private:
        SDL_Window *_window;
        SDL_Surface *_drawSurface;
};

extern "C"{
    Interface * Interface_Init(){
        return new SDL();
    }
}

#endif