#ifndef SDL_INTERFACE_H
#define SDL_INTERFACE_H

#include "interface.hpp"
#include <SDL2/SDL.h>

class SDL : public Interface{
    public:
        SDL();
        SDL(SDL const & obj);
        ~SDL();

        int open_window(int width, int height);
        std::string getName();
    private:
        SDL_Window *_window;
};

#endif