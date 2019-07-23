#include "game.class.hpp"


Game::Game(int x, int h) : map(x, h){
    this->DLLS[SDL] = "interface/sdl.interface.dll";
    this->DLLS[GLFW] = "interface/glfw.interface.dll";
    this->DLLS[SFML] = "interface/sfml.interface.dll";
}
Game::Game(Game & obj) : interface(obj.interface), interface_instance(obj.interface_instance), map(obj.map){}
Game::~Game(){}

void Game::update(){}
void Game::render(){
    this->interface_instance->clear();
    
    this->player.render(*this->interface_instance);
    this->apple.render(*this->interface_instance);

    this->interface_instance->drawBlock(5,5,Color(RED));

    this->interface_instance->updateView();
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
    this->interface_instance = init(this->map.getW(), this->map.getH(), BLOCK);
}

void handleKey(int key, int scancode, int mods){
    std::cout << "key: " << key << "\tscancode" << scancode << "\tmod" << mods << std::endl;
}

void Game::run(){
    this->loadDll();
    std::cout << "Loaded dll: " << this->interface_instance->getName() << std::endl;
    
    this->interface_instance->open_window();

    this->interface_instance->bindKeyCallback(handleKey);

    while(!this->interface_instance->closing()){
        this->update();
        this->render();
    }
}
