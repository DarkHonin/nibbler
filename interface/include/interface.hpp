#ifndef DINTERFACE_H
#define DINTERFACE_H
#include <string>
#include <iostream>

class InterfaceException : public std::exception{};

typedef void (*key_callback)(int key, int scancode, int mods);

class Color{
    public:
        char r;
        char g;
        char b;
        Color(char r, char g, char b);
        Color(Color const & obj);
        Color();
        ~Color();
        void apply(Color e);
};

class Interface{
    public:

        virtual int open_window() = 0;

        virtual void drawBlock(int x, int y, Color c) = 0;

        virtual void prerender() = 0;
        virtual void postrender() = 0;

        virtual void bindKeyCallback(const key_callback) = 0;
        virtual bool closing() = 0;

        virtual std::string getName() = 0;
};



// width/height = amount of blocks
// block_size = the length in pixels
typedef Interface* (*InterfaceInit)(int width, int height, int block_size);

#endif