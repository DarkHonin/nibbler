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
    this->interface_instance = init();
}

void Game::run(){
    std::cout << "Loaded dll: " << this->interface_instance->getName() << std::endl;
    this->interface_instance->open_window(800, 600);
    std::cout << "Window open called" << std::endl;
    while(true){
        this->interface_instance->updateView();
    }
}
