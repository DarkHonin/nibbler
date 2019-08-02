#ifndef GLFW_INTERFACE_H
#define GLFW_INTERFACE_H

#define GL_SILENCE_DEPRECATION

#include "interface.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define VERTEX_SHADER "vertexShader.glsl"
#define FRAGMENT_SHADER "fragmentShader.glsl"

class GLFW : public Interface{
    public:

        GLFW(int blockx, int blocky, int blocksize);
        GLFW(GLFW const & obj);
        ~GLFW();

        void drawBlock(int x, int y, Color c);
        void drawText(int x, int y, std::string const txt);

        void prerender();
        void postrender();

        void bindKeyCallback(const key_callback);
        bool closing();

        std::string getName();
    private:
        GLFWwindow *_window;

        int _xBlocks;
        int _yBlocks;
        int _blockSize;

        GLfloat _blockW;
        GLfloat _blockH;

        GLuint shader;
        GLuint vertexArray;
        GLuint VAO;
        GLuint EBO;
};

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

extern "C"{
    Interface * Interface_Init(int w, int h, int b){
        return new GLFW(w, h, b);
    }
}

#endif