#include "game.class.hpp"
#include <time.h>

static Game *instance;

Game::Game(int x, int h) : w(x), h(h), state(Start){
    this->DLLS[SDL] = "interface/sdl.interface.dll";
    this->DLLS[GLFW] = "interface/glfw.interface.dll";
    this->DLLS[SFML] = "interface/sfml.interface.dll";
    apple.place(*this);
    player.place(*this);
    instance = this;
}

Game::Game(Game & obj) : interface(obj.interface), interface_instance(obj.interface_instance), w(obj.w), h(obj.h){}
Game::~Game(){}

bool inputLock = false;

void Game::update(int d){
    if(state == Running){
        inputLock = false;
        player.update(*this);
    }
}
void Game::render(int d){
    interface_instance->prerender();
    
    for(int c = 0; c < getW(); c++){
        interface_instance->drawBlock(c,0,Color(255, 255, 255));
        interface_instance->drawBlock(c,getH() - 1,Color(255, 255, 255));
    }
    for(int c = 0; c < getH(); c++){
        interface_instance->drawBlock(0,c,Color(255, 255, 255));
        interface_instance->drawBlock(getW() - 1, c,Color(255, 255, 255));
    }

    apple.render(*this->interface_instance);
    player.render(*this->interface_instance);

    switch (state)
    {
    case Start:
        interface_instance->drawText(1, 1, "Press w,a,s or d to start");
        break;
    
    default:
        break;
    }
    
    interface_instance->postrender();
}

void Game::loadDll(std::string const define){
    char *err;

    if(this->interface){
        printf("Unloading current dll\n");
        delete interface_instance;
        dlclose(this->interface);
    };
    this->interface = dlopen(this->DLLS[define].c_str(), RTLD_NOW | RTLD_GLOBAL);
    err = dlerror();
    if(err) std::cout << err << std::endl;
    InterfaceInit init = (InterfaceInit)dlsym(this->interface, "Interface_Init");
    err = dlerror();
    if(err) std::cout << err << std::endl;
    this->interface_instance = init(getW(), getH(), BLOCK);
}

void handleKey(int key, int scancode, int mods){
    std::cout << "Char: "<< (char)key << "\tkey: " << key << "\tscancode: " << scancode << "\tmod: " << mods << std::endl;
    if((char)key == '1'){
        instance->loadDll(GLFW);
        instance->state = Pause;
        return;
    };
    if((char)key == '2'){
        instance->loadDll(SDL);
        instance->state = Pause;
        return;
    };
    switch(instance->state){
        case Start:
            if((char)key == 'W' || (char)key == 'A' || (char)key == 'S' || (char)key == 'D'){
                instance->state = Running;
                instance->player.handleKey(key);
                printf("Game starting\n");
            }
        case Pause:
            if(key == 'R')
                instance->state = Running;
            break;
        case Running:
            if(key == ' ')
                instance->state = Pause;
            else
                instance->player.handleKey(key);
    }
}

void Game::run(){
    this->loadDll(SDL);

    std::cout << "Loaded dll: " << this->interface_instance->getName() << std::endl;
    
    this->interface_instance->bindKeyCallback(handleKey);

    clock_t start = clock();
    int d = 0;

    while(!this->interface_instance->closing()){
        d += (double)clock() - start;
        if(d >= 100000000 - (player.getScore() * 10000000)){
            this->update(d);
            d = 0;
            start = clock();
        }
        this->render(d);
    }

}

int Game::getW() const{ return this->w; }
int Game::getH() const{ return this->h; }