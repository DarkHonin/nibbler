#ifndef GLFW_INTERFACE_H
#define GLFW_INTERFACE_H

#define GL_SILENCE_DEPRECATION

#include "interface.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define VERTEX_SHADER "vertexShader.glsl"
#define FRAGMENT_SHADER "gragmentShader.glsl"

class GLFW : public Interface{
    public:

        GLFW(int w, int h, int b);
        GLFW(GLFW const & obj);
        ~GLFW();

        int open_window();

        void drawBlock(int x, int y, Color c = Color(0,0,0));

        void updateView();
        void clear();

        void bindKeyCallback( const key_callback);
        bool closing();

        std::string getName();
    private:
        GLFWwindow *_window;
        key_callback onKey;
        int width;
        int height;
        int block;

        GLuint shader;
};

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

extern "C"{
    Interface * Interface_Init(int w, int h, int b){
        return new GLFW(w, h, b);
    }
}

#endif