#include "SDL.class.hpp"

SDL::SDL(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::exception();
}

SDL::SDL(SDL const & obj) : _window(obj._window){}

SDL::~SDL(){}

int SDL::open_window(int w, int h){
    this->_window = SDL_CreateWindow(this->getName().c_str(), 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        w, h, 
                                        SDL_WINDOW_SHOWN);
    return 1;
}
std::string SDL::getName(){
    return std::string("SDLibbler");
}