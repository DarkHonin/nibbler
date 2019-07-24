#include "GLFW.class.hpp"
#include <iostream>

GLuint LoadShaders(const char* vertShaderPath, const char* fragShaderPath);

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
    glfwSetErrorCallback([](int code, const char *message) {std::cout << "GLFW Error " << code << ": "<< message << std::endl;});
    
    this->_window = glfwCreateWindow(this->width * this->block, this->height * this->block, this->getName().c_str(), NULL, NULL);
    if(!this->_window){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(this->_window);
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
    }

    float array[] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    glGenBuffers(1, &vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArray);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), array, GL_STATIC_DRAW);

    glViewport(0, 0, this->width * this->block, this->height * this->block);
    shader = LoadShaders(VERTEX_SHADER, FRAGMENT_SHADER);

}

GLFW::GLFW(GLFW const & obj) :  width(obj.width), height(obj.height), block(obj.block),_window(obj._window){}

GLFW::~GLFW(){
    if(this->_window)
        glfwDestroyWindow(this->_window);
    glfwTerminate();
}


int GLFW::open_window(){
    return 0;
}

void GLFW::drawBlock(int x, int y, Color c){
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool GLFW::closing(){
    return glfwWindowShouldClose(this->_window);
}

void GLFW::bindKeyCallback(key_callback const key){ this->onKey = key; }

void GLFW::prerender(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(this->shader);
}

void GLFW::postrender(){
    glfwSwapBuffers(this->_window);
    glfwPollEvents();
}

std::string GLFW::getName(){
    return std::string("GLFWibbler");
}