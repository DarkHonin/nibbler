#include "GLFW.class.hpp"
#include <iostream>

key_callback GLFW::onKey = 0;

const GLfloat GLFW::g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

GLuint vertexbuffer;

static void readKey(GLFWwindow *window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        if(GLFW::onKey) GLFW::onKey(key, scancode, mods);
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

    }
}

GLFW::GLFW(int w, int h, int b): width(w), height(h), block(b){
    glewExperimental = true;
    if (!glfwInit())
        throw new InterfaceException();
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
}

GLFW::GLFW(GLFW const & obj) :  width(obj.width), height(obj.height), block(obj.block),_window(obj._window){}

GLFW::~GLFW(){
    if(this->_window)
        glfwDestroyWindow(this->_window);
    if(this->VertexArrayID) glDeleteBuffers(1, &(this->VertexArrayID));
    glfwTerminate();
}


int GLFW::open_window(){
    this->_window = glfwCreateWindow(this->width * this->block, this->height * this->block, this->getName().c_str(), NULL, NULL);
     if(!this->_window)
        throw new InterfaceException;
    glfwMakeContextCurrent(this->_window);
    glewExperimental = true;

    if(glewInit() != GLEW_OK)
        throw new InterfaceException();

    glGenBuffers(1, &(this->VertexArrayID));
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexArrayID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    return 1;
}

void GLFW::drawBorder(){
   glBindBuffer(GL_ARRAY_BUFFER, this->VertexArrayID);
   glEnableClientState(GL_VERTEX_ARRAY);
   glDrawElements(GL_TRIANGLES, 3, GL_FLOAT, 0);
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
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

void GLFW::bindKeyCallback(key_callback const key){ GLFW::onKey = key; }

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