#include "GLFW.class.hpp"
#include <iostream>

GLuint LoadShaders(const char* vertShaderPath, const char* fragShaderPath);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }  

key_callback key_call = 0;

void key(GLFWwindow *e, int a, int b, int c, int d){
    if(key_call)
        key_call(a, b, c);
    if(a == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(e, 1);
}

GLFW::GLFW(int w, int h, int b): _xBlocks(w), _yBlocks(h), _blockSize(b){
    glewExperimental = true;
    if (!glfwInit())
        throw new InterfaceException();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    //glfwWindowHint(GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetErrorCallback([](int code, const char *message) {std::cout << "GLFW Error " << code << ": "<< message << std::endl;});
    
    this->_window = glfwCreateWindow(_xBlocks * _blockSize, _yBlocks * _blockSize, this->getName().c_str(), NULL, NULL);
    if(!this->_window){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(this->_window);
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
    }

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    _blockW = ((float)1/_yBlocks), _blockH = ((float)1/_yBlocks);

    std::cout << _blockW << " " << _blockH << std::endl;
    float border_size = 0.005f;
    float vertices[] = {
        _blockW - border_size,  _blockH - border_size, 0.0f,  
        _blockW - border_size, -_blockH + border_size, 0.0f,  
        -_blockW + border_size, -_blockH + border_size, 0.0f,  
        -_blockW + border_size,  _blockH - border_size, 0.0f
    };

    unsigned int indices[] = {  
        0, 1, 3,   
        1, 2, 3 
    };

    printf("Loading vetecies\n");
    glGenBuffers(1, &vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArray);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    printf("Verticies loaded\n");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArray);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
    
    shader = LoadShaders(VERTEX_SHADER, FRAGMENT_SHADER);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    glfwSetKeyCallback(_window, &key);
    std::cout << "Init of GLFW compleat" << std::endl;
}

GLFW::GLFW(GLFW const & obj) :  _xBlocks(obj._xBlocks), _yBlocks(obj._yBlocks), _blockSize(obj._blockSize),_window(obj._window){}

GLFW::~GLFW(){
  
}

void GLFW::drawBlock(int x, int y, Color c){
    glUseProgram(shader);

    int vertexColorLocation = glGetUniformLocation(shader, "color");
    glUniform4f(vertexColorLocation, (float)(c.r / 255), (float)(c.g / 255), (float)(c.b / 255), 1.0f);

    float XPos = (((x * _blockW) - .5f) / .5f) + _blockW;
    float YPos = (((y * _blockH) - .5f) / .5f) + _blockH;
    int vertexPosLocation = glGetUniformLocation(shader, "pos");
    glUniform4f(vertexPosLocation, XPos, YPos, 0.0f, 0.0f);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GLFW::drawText(int x, int y, std::string text){
    float XPos = (((x * _blockW) - .5f) / .5f) + _blockW;
    float YPos = (((y * _blockH) - .5f) / .5f) + _blockH;
}

bool GLFW::closing(){
    return glfwWindowShouldClose(this->_window);
}

void GLFW::close(){
printf("Closing sdl window\n");
      if(this->_window)
        glfwDestroyWindow(this->_window);
    glfwTerminate();
    printf("SDL window closed\n");
}

void GLFW::bindKeyCallback(key_callback const key){ key_call = key; }

void GLFW::prerender(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLFW::postrender(){
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

std::string GLFW::getName(){
    return std::string("GLFWibbler");
}