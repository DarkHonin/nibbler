#include "game.class.hpp"
#include <time.h>

static Game *instance;
std::string DLL = SDL;

Game::Game(int x, int h) : state(Start), w(x), h(h) {
    this->DLLS[SDL] = "interface/sdl.interface.dll";
    this->DLLS[GLFW] = "interface/glfw.interface.dll";
    this->DLLS[NCUR] = "interface/ncur.interface.dll";
    apple.place(*this);
    player.place(*this);
    instance = this;
}

Game::Game(Game & obj) : interface(obj.interface), interface_instance(obj.interface_instance), w(obj.w), h(obj.h){}
Game::~Game(){}

bool inputLock = false;

void Game::update(){
    if(state == Running){
        inputLock = false;
        player.update(*this);
        
    }
}

void Game::render(){
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
    case End:
        interface_instance->drawText(1, 1, "You died, Score: " + std::to_string(player.getScore()));
        break;
    case Pause:
        interface_instance->drawText(1, 1, "Paused press R to resume");
        break;
    default:
        break;
    }
    
    interface_instance->postrender();
}

void Game::doNoting(){

}

void handleKey(int key, int scancode, int mods){
    char rc = (toupper(key));
    std::cout << "Char: "<< rc << "\tkey: " << key << "\tscancode: " << scancode << "\tmod: " << mods << std::endl;
    if(rc== '1' && DLL != GLFW){
        DLL = GLFW;
        instance->state = Switching;
        return;
    };
    if(rc== '2' && DLL != SDL){
        DLL = SDL;
        instance->state = Switching;
        return;
    };
     if(rc== '3'&& DLL != NCUR){
        DLL = NCUR;
        instance->state = Switching;
        return;
    };
    switch(instance->state){
        case Start:
            if(rc== 'W' || rc== 'A' || rc== 'S' || rc== 'D'){
                instance->state = Running;
                instance->player.handleKey(key);
                printf("Game starting\n");
            }
        case Pause:
            if(rc== 'R')
                instance->state = Running;
            break;
        case Running:
            if(rc== ' ')
                instance->state = Pause;
            else
                instance->player.handleKey(key);
            break;
        case End:
            if(rc== ' '){
                instance->player.reset(*instance);
                instance->apple.place(*instance);
                instance->state = Start;
            }
            break;
        case Switching: break;
    }
}
void Game::loadDll(std::string const define){
    char *err;

    if(this->interface){
        printf("Unloading current dll\n");
        interface_instance->close();
        dlclose(this->interface);
        printf("Closed dll\n");
    };
    this->interface = dlopen(this->DLLS[define].c_str(), RTLD_NOW | RTLD_GLOBAL);
    err = dlerror();
    if(err) std::cout << err << std::endl;
    else printf("DLL opened\n");
    InterfaceInit init = (InterfaceInit)dlsym(this->interface, "Interface_Init");
    err = dlerror();
    if(err) std::cout << err << std::endl;
    else printf("Entrypoint allocated\n");
    this->interface_instance = init(getW(), getH(), BLOCK);
    this->interface_instance->bindKeyCallback(handleKey);
}


void Game::run(){
    while(true){
        this->loadDll(DLL);

        std::cout << "Loaded dll: " << this->interface_instance->getName() << std::endl;
        
        clock_t start = clock();
        int d = 0;
        
        while(true){

            d += (double)clock() - start;
            if(d >= 100000000 - (player.getScore() * 10000000)){
                this->update();

                d = 0;
                start = clock();
            }
            this->render();
            interface_instance->pollEvents();
            if(state == Switching)
                break;
            if(this->interface_instance->closing())
                return;
        }
        if(state == Switching)
            state = Pause;
    }

}

int Game::getW() const{ return this->w; }
int Game::getH() const{ return this->h; }