#include "game.class.hpp"

Game::Game(){
    this->loadDll();
}
Game::Game(Game & obj) : interface(obj.interface), interface_instance(obj.interface_instance){}
Game::~Game(){}

void Game::update(){}
void Game::render(){}

void Game::loadDll(std::string const path){
   char *err;

   if(this->interface) dlclose(this->interface);
   this->interface = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);
   err = dlerror();
   if(err) std::cout << err << std::endl;
   InterfaceInit init = (InterfaceInit)dlsym(this->interface, "Interface_Init");
   err = dlerror();
    if(err) std::cout << err << std::endl;
    this->interface_instance = init(WIDTH, HEIGHT, BLOCK);
}

void handleKey(int key, int scancode, int mods){
    std::cout << "key: " << key << "\tscancode" << scancode << "\tmod" << mods << std::endl;
}

void Game::run(){
    std::cout << "Loaded dll: " << this->interface_instance->getName() << std::endl;
    
    this->interface_instance->open_window();

    this->interface_instance->bindKeyCallback(handleKey);

    while(!this->interface_instance->closing()){
        this->interface_instance->clear();
        this->interface_instance->drawBorder();
        this->interface_instance->updateView();
    }
}
