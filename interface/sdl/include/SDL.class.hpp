#ifndef SDL_INTERFACE_H
#define SDL_INTERFACE_H

#include "interface.hpp"
#include <SDL2/SDL.h>

class SDL : public Interface{
    public:
        static key_callback keyHook;

        SDL(int blockx, int blocky, int blocksize);
        SDL(SDL const & obj);
        ~SDL();

        void drawBlock(int x, int y, Color c);
        void drawText(int x, int y, std::string const txt);

        void prerender();
        void postrender();

        void bindKeyCallback(const key_callback);
        bool closing();
        void close();

        std::string getName();
    private:
        SDL_Window *_window;
        SDL_Surface *_drawSurface;

        int _xBlocks;
        int _yBlocks;
        int _blockSize;
};

extern "C"{
    Interface * Interface_Init(int w, int h, int b){
        printf("Creating new sdl instance\n");
        return new SDL(w, h, b);
    }
}

#endif