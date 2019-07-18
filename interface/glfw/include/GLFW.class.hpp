#ifndef GLFW_INTERFACE_H
#define GLFW_INTERFACE_H

#define GL_SILENCE_DEPRECATION

#include "interface.hpp"
#include <GLFW/glfw3.h>

class GLFW : public Interface{
    public:
        GLFW();
        GLFW(GLFW const & obj);
        ~GLFW();

        int open_window(int width, int height);
        void drawBorder();
        void updateView();

        std::string getName();
    private:
        GLFWwindow *_window;
};

extern "C"{
    Interface * Interface_Init(){
        return new GLFW();
    }
}

#endif