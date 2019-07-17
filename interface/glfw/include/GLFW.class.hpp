#ifndef GLFW_INTERFACE_H
#define GLFW_INTERFACE_H

#include "interface.hpp"
#include <GLFW/glfw3.h>

class GLFW : public Interface{
    public:
        GLFW();
        GLFW(GLFW const & obj);
        ~GLFW();

        int open_window(int width, int height);
        std::string getName();
    private:
        GLFWwindow *_window;
};

extern "C"{
    Interface * InterfaceInit(){
        return new GLFW();
    }
}

#endif