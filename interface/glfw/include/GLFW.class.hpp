#ifndef GLFW_INTERFACE_H
#define GLFW_INTERFACE_H

#define GL_SILENCE_DEPRECATION

#include "interface.hpp"
#include <GLFW/glfw3.h>

class GLFW : public Interface{
    public:
        static key_callback onKey;

        GLFW();
        GLFW(GLFW const & obj);
        ~GLFW();

        int open_window(int width, int height);

        void drawBorder();
        void updateView();

        void bindKeyCallback( const key_callback);
        bool closing();

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