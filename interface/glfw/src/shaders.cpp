#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::string LoadFileToString(const char* filepath)
{
    std::string fileData;
    std::ifstream stream(filepath, std::ios::in);

    if (stream.is_open())
    {
        std::string line = "";
        while (getline(stream, line))
            fileData += "\n" + line;
        stream.close();
    }

    return fileData;
}

GLuint LoadShaders(const char* vertShaderPath, const char* fragShaderPath)
{
    std::cout << "Creating shaders" << std::endl;
    
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::cout << "Reading vert" << std::endl;
    std::string vertShaderSource = LoadFileToString(vertShaderPath);
    std::cout << "Reading frag" << std::endl;
    std::string fragShaderSource = LoadFileToString(vertShaderPath);

    const char* rawVertShaderSource = vertShaderSource.c_str();
    const char* rawFragShaderSource = fragShaderSource.c_str();

    glShaderSource(VertexShaderID, 1, &rawVertShaderSource, NULL);
    glShaderSource(FragmentShaderID, 1, &rawFragShaderSource, NULL);
    std::cout << "Compiling" << std::endl;
    glCompileShader(VertexShaderID);
    glCompileShader(FragmentShaderID);

    GLuint program = glCreateProgram();
    glAttachShader(program, VertexShaderID);
    glAttachShader(program, FragmentShaderID);
    glLinkProgram(program);
	
	glDetachShader(program, VertexShaderID);
	glDetachShader(program, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

    return program;
}
