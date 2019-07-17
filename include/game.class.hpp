#ifndef NIBBLER_H
#define NIBBLER_H

#include "interface.hpp"
#include <dlfcn.h>

#define SDL "interface/sdl.interface.dll"
#define GLFW "interface/glfw.interface.dll"
#define SFML "interface/sfml.interface.dll"

class Game{
    public:
        Game();
        Game(Game & obj);
        ~Game();

        void update();
        void render();

        void loadDll(std::string const path = GLFW);
        void run();
    private:
        void *interface;
        InterfaceInit interface_init; 
};

#endif