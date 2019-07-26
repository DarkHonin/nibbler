#include "game.class.hpp"


Game::Game(int x, int h) : map(x, h){
    this->DLLS[SDL] = "interface/sdl.interface.dll";
    this->DLLS[GLFW] = "interface/glfw.interface.dll";
    this->DLLS[SFML] = "interface/sfml.interface.dll";
    apple.place(map);
    player.place(map);
}

Game::Game(Game & obj) : interface(obj.interface), interface_instance(obj.interface_instance), map(obj.map){}
Game::~Game(){}

void Game::update(){}
void Game::render(){
    interface_instance->prerender();
    
    for(int c = 0; c < map.getW(); c++){
        interface_instance->drawBlock(c,0,Color(255, 255, 255));
        interface_instance->drawBlock(c,map.getH() - 1,Color(255, 255, 255));
    }
    for(int c = 0; c < map.getH(); c++){
        interface_instance->drawBlock(0,c,Color(255, 255, 255));
        interface_instance->drawBlock(map.getW() - 1, c,Color(255, 255, 255));
    }

    apple.render(*this->interface_instance);

    player.render(*this->interface_instance);
    
    interface_instance->postrender();
}

void Game::loadDll(std::string const define){
    char *err;

    if(this->interface) dlclose(this->interface);
    this->interface = dlopen(this->DLLS[define].c_str(), RTLD_NOW | RTLD_GLOBAL);
    err = dlerror();
    if(err) std::cout << err << std::endl;
    InterfaceInit init = (InterfaceInit)dlsym(this->interface, "Interface_Init");
    err = dlerror();
    if(err) std::cout << err << std::endl;
    this->interface_instance = init(map.getW(), map.getH(), BLOCK);
}

void handleKey(int key, int scancode, int mods){
    std::cout << "key: " << key << "\tscancode: " << scancode << "\tmod: " << mods << std::endl;
}

void Game::run(){
    this->loadDll();

    std::cout << "Loaded dll: " << this->interface_instance->getName() << std::endl;
    
    this->interface_instance->bindKeyCallback(handleKey);

    while(!this->interface_instance->closing()){
        this->update();
        this->render();
    }

}
