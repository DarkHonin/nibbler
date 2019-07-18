#include "GLFW.class.hpp"
#include <iostream>
GLFW::GLFW(){
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
}

GLFW::GLFW(GLFW const & obj) : _window(obj._window){}

GLFW::~GLFW(){
    glfwDestroyWindow(this->_window);
}

int GLFW::open_window(int width, int height){
    this->_window = glfwCreateWindow(width, height, this->getName().c_str(), NULL, NULL);
    
    glfwMakeContextCurrent(this->_window);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);
    return 1;
}

void GLFW::drawBorder(){

}

void GLFW::updateView(){
    glfwSwapBuffers(this->_window);
}


std::string GLFW::getName(){
    return std::string("GLFWibbler");
}