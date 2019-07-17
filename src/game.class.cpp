#include "game.class.hpp"

Game::Game(){
    this->loadDll();
}
Game::Game(Game & obj){}
Game::~Game(){}

void Game::update(){}
void Game::render(){}

void Game::loadDll(std::string const path){
   if(this->interface) dlclose(this->interface);
   this->interface = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);
   *(void **)(& this->interface_init) = dlsym(this->interface, "InterfaceInit");
}

void Game::run(){
    Interface *hold = this->interface_init();
}
