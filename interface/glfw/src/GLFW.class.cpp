#include "GLFW.class.hpp"
#include <iostream>


GLFW::GLFW(int w, int h, int b): width(w), height(h), block(b){
    glewExperimental = true;
    if (!glfwInit())
        throw new InterfaceException();
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
}

GLFW::GLFW(GLFW const & obj) :  width(obj.width), height(obj.height), block(obj.block),_window(obj._window){}

GLFW::~GLFW(){
    if(this->_window)
        glfwDestroyWindow(this->_window);
    glfwTerminate();
}


int GLFW::open_window(){
    this->_window = glfwCreateWindow(this->width * this->block, this->height * this->block, this->getName().c_str(), NULL, NULL);
     if(!this->_window){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 0;
     }
    glfwMakeContextCurrent(this->_window);
    glViewport(0, 0, 800, 600);
    /*
    glewExperimental = true;

    if(glewInit() != GLEW_OK)
        throw new InterfaceException();
     */

    return 1;
}

void GLFW::drawBorder(){
   
}

void GLFW::drawBlock(int x, int y, int width, int height){
    glBegin(GL_QUADS);
    glVertex2i(x * this->block, y * this->block);
    glVertex2i((x + width) * this->block, y * this->block);
    glVertex2i((x + width) * this->block, (y + height) * this->block);
    glVertex2i(x * this->block, (y + height) * this->block);
    glEnd();
}

bool GLFW::closing(){
    return glfwWindowShouldClose(this->_window);
}

void GLFW::bindKeyCallback(key_callback const key){ this->onKey = key; }

void GLFW::updateView(){
    glfwSwapBuffers(this->_window);
    glfwPollEvents();
}

void GLFW::clear(){
    glClear( GL_COLOR_BUFFER_BIT );
}

std::string GLFW::getName(){
    return std::string("GLFWibbler");
}