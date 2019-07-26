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
    printf("Compiling shader\n");
    
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    printf("VertexShader:\t%s\nFragmentShader:\t%s\n", vertShaderPath, fragShaderPath);
    std::string vertShaderSource = LoadFileToString(vertShaderPath);
    std::string fragShaderSource = LoadFileToString(fragShaderPath);

    const char* rawVertShaderSource = vertShaderSource.c_str();
    const char* rawFragShaderSource = fragShaderSource.c_str();

    glShaderSource(VertexShaderID, 1, &rawVertShaderSource, NULL);
    glShaderSource(FragmentShaderID, 1, &rawFragShaderSource, NULL);
    
    
    int  success;
    char infoLog[512];

    glCompileShader(VertexShaderID);
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(VertexShaderID, 255, NULL, infoLog);
        printf("GLVertexShader::Log:: %s\n", infoLog);
    }
    
    glCompileShader(FragmentShaderID);
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(FragmentShaderID, 255, NULL, infoLog);
        printf("GLFragmentShader::Log:: %s\n", infoLog);
    }
    GLuint program = glCreateProgram();
    glAttachShader(program, VertexShaderID);
    glAttachShader(program, FragmentShaderID);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("Program::Log:: %s\n", infoLog);
    }
	
	glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);  

    return program;
}
