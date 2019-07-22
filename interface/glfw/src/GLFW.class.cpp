#include "GLFW.class.hpp"
#include <iostream>

static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

static GLuint vertexbuffer;

GLuint LoadShaders(const char* vertShaderPath, const char* fragShaderPath);

GLFW::GLFW(int w, int h, int b): width(w), height(h), block(b), shader(LoadShaders(VERTEX_SHADER, FRAGMENT_SHADER)){
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

    std::cout << "GEN" << std::endl;
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    std::cout << "BIND" << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    std::cout << "BUFFER" << std::endl;
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glUseProgram(this->shader);
    return 1;
}

void GLFW::drawBlock(int x, int y, Color c){
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

std::string GLFW::getName(){
    return std::string("GLFWibbler");
}