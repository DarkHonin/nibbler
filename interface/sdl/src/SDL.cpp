#include "SDL.class.hpp"

key_callback SDL::keyHook = 0;
bool is_close = false;

SDL::SDL(int w, int h, int b) : _xBlocks(w), _yBlocks(h), _blockSize(b){
    printf("Initing\n");
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw InterfaceException();
    else
        printf("SDL ok\n");

    this->_window = SDL_CreateWindow(this->getName().c_str(), 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        w * b, h * b, 
                                        SDL_WINDOW_SHOWN);

    if(!this->_window)
        throw new InterfaceException();
    else
        printf("SDL window created\n");
    this->_drawSurface = SDL_GetWindowSurface(this->_window);
}

SDL::SDL(SDL const & obj) : _window(obj._window){}

SDL::~SDL(){
    
    //SDL_Quit();
}

void SDL::close(){
printf("Closing sdl window\n");
    SDL_DestroyWindow( this->_window );
    SDL_Quit();
    printf("SDL window closed\n");
}


void SDL::drawBlock(int x, int y, Color c){
    SDL_Rect *r = new SDL_Rect();
    r->x = (x * _blockSize) + 1;
    r->y = ((_yBlocks - y - 1) * _blockSize) + 1;
    r->w = _blockSize - 2;
    r->h = _blockSize - 2;
    SDL_FillRect( this->_drawSurface, r, SDL_MapRGB( this->_drawSurface->format, c.r, c.g, c.b) );
    delete r;
}
void SDL::drawText(int x, int y, std::string const txt){

}

void SDL::prerender(){
    SDL_FillRect( this->_drawSurface, NULL, SDL_MapRGB( this->_drawSurface->format, 0x00, 0x00, 0x00 ) );
   
}
void PollEvents(){
    SDL_Event e;
    char *keyname;
    while(SDL_PollEvent(&e) != 0){
        if( e.type == SDL_QUIT ) is_close = true;
        if( e.type == SDL_KEYUP ){
            if(strcmp(SDL_GetKeyName(e.key.keysym.sym), "Escape") == 0){
                is_close = true;
                return;
            }
            if(SDL::keyHook)
                switch(e.key.keysym.scancode){
                    case SDL_SCANCODE_1:
                        return SDL::keyHook('1', e.key.keysym.scancode, e.key.keysym.mod);
                    case SDL_SCANCODE_2:
                        return SDL::keyHook('2', e.key.keysym.scancode, e.key.keysym.mod);
                    case SDL_SCANCODE_3:
                        return SDL::keyHook('3', e.key.keysym.scancode, e.key.keysym.mod);
                    case SDL_SCANCODE_SPACE:
                        return SDL::keyHook(' ', e.key.keysym.scancode, e.key.keysym.mod);
                    case SDL_SCANCODE_A:
                        return SDL::keyHook('A', e.key.keysym.scancode, e.key.keysym.mod);
                    case SDL_SCANCODE_W:
                        return SDL::keyHook('W', e.key.keysym.scancode, e.key.keysym.mod);
                    case SDL_SCANCODE_D:
                        return SDL::keyHook('D', e.key.keysym.scancode, e.key.keysym.mod);
                    case SDL_SCANCODE_S:
                        return SDL::keyHook('S', e.key.keysym.scancode, e.key.keysym.mod);
                    case SDL_SCANCODE_R:
                        return SDL::keyHook('R', e.key.keysym.scancode, e.key.keysym.mod);
                    default:
                        break;
                }
            
        }
    }
}
void SDL::postrender(){
    SDL_UpdateWindowSurface( this->_window );
    PollEvents();
}

void SDL::bindKeyCallback( const key_callback hook){
    SDL::keyHook = hook;
}
bool SDL::closing(){
    return is_close;
}

std::string SDL::getName(){
    return std::string("SDLibbler");
}