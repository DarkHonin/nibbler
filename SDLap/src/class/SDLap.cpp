#include "SDLap.hpp"
#include <iostream>

SDLap::SDLap(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
	    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
}
SDLap::~SDLap(){}