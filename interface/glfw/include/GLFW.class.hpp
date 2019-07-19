#ifndef GLFW_INTERFACE_H
#define GLFW_INTERFACE_H

#define GL_SILENCE_DEPRECATION

#include "interface.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLFW : public Interface{
    public:
        static key_callback onKey;
        static const GLfloat g_vertex_buffer_data[];
        GLuint VertexArrayID;

        GLFW(int w, int h, int b);
        GLFW(GLFW const & obj);
        ~GLFW();

        int open_window();

        void drawBorder();
        void drawBlock(int x, int y, int w = 1, int h = 1);

        void updateView();
        void clear();

        void bindKeyCallback( const key_callback);
        bool closing();



        std::string getName();
    private:
        GLFWwindow *_window;
        int width;
        int height;
        int block;
};

GLuint LoadShaders(const char* vertes, const char *fragment);

extern "C"{
    Interface * Interface_Init(int w, int h, int b){
        return new GLFW(w, h, b);
    }
}

#endif