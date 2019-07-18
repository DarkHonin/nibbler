#include "GLFW.class.hpp"
#include <iostream>

key_callback GLFW::onKey = 0;

static void readKey(GLFWwindow *window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        if(GLFW::onKey) GLFW::onKey(key, scancode, mods);
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

    }
}

GLFW::GLFW(){
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
}

GLFW::GLFW(GLFW const & obj) : _window(obj._window){}

GLFW::~GLFW(){
    glfwDestroyWindow(this->_window);
    glfwTerminate();
}

int GLFW::open_window(int width, int height){
    this->_window = glfwCreateWindow(width, height, this->getName().c_str(), NULL, NULL);
     if(!this->_window)
        throw new InterfaceException;
    glfwMakeContextCurrent(this->_window);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);
    glfwSetKeyCallback(this->_window, &readKey);
    glfwSetWindowShouldClose(this->_window, GLFW_FALSE);
    return 1;
}

void GLFW::drawBorder(){

}

bool GLFW::closing(){
    return glfwWindowShouldClose(this->_window);
}


void GLFW::bindKeyCallback(key_callback const key){ GLFW::onKey = key; }

void GLFW::updateView(){
    glfwSwapBuffers(this->_window);
    glfwPollEvents();
}


std::string GLFW::getName(){
    return std::string("GLFWibbler");
}