#include "GLFW.class.hpp"

GLFW::GLFW(){}

GLFW::GLFW(GLFW const & obj) : _window(obj._window){}

GLFW::~GLFW(){}

int GLFW::open_window(int width, int height){
    this->_window = glfwCreateWindow(width, height, this->getName().c_str(), NULL, NULL);
    return 1;
}
std::string GLFW::getName(){
    return std::string("GLFWibbler");
}