#ifndef GLFWDLL_H
#define GLFWDLL_H

#include <string>

class GLFWDll{
    public:
        GLFWDll(void);
        std::string getName(void);
};

#pragma export(GLFWDll::getName)

#endif