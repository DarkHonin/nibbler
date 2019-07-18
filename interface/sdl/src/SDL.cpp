#include "SDL.class.hpp"

key_callback SDL::keyHook = 0;
bool close = false;

SDL::SDL(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw InterfaceException();
}

SDL::SDL(SDL const & obj) : _window(obj._window){}

SDL::~SDL(){
    SDL_DestroyWindow( this->_window );
    SDL_Quit();
}

int SDL::open_window(int w, int h){
    this->_window = SDL_CreateWindow(this->getName().c_str(), 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        w, h, 
                                        SDL_WINDOW_SHOWN);
    if(!this->_window){
        throw new InterfaceException();
    }
    this->_drawSurface = SDL_GetWindowSurface(this->_window);
    return 1;
}

void SDL::drawBorder(){}

void PollEvents(){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
        std::cout << e.type << std::endl;
        if( e.type == SDL_QUIT ) close = true;
        else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
            if(SDL::keyHook) SDL::keyHook(e.key.keysym.sym, e.key.keysym.scancode, e.key.keysym.mod);
        }
    }
}

void SDL::updateView(){
    SDL_FillRect( this->_drawSurface, NULL, SDL_MapRGB( this->_drawSurface->format, 0xFF, 0xFF, 0xFF ) );
    SDL_UpdateWindowSurface( this->_window );
    PollEvents();
    SDL_Delay(200);
}

void SDL::bindKeyCallback( const key_callback hook){
    SDL::keyHook = hook;
}
bool SDL::closing(){
    return close;
}

std::string SDL::getName(){
    return std::string("SDLibbler");
}