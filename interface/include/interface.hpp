#ifndef DINTERFACE_H
#define DINTERFACE_H
#include <string>
#include <iostream>

class InterfaceException : public std::exception{};

typedef void (*key_callback)(int key, int scancode, int mods);

class Interface{
    public:

        virtual int open_window() = 0;

        virtual void drawBorder() = 0;
        virtual void drawBlock(int x, int y, int w, int h) = 0;

        virtual void updateView() = 0;
        virtual void clear() = 0;

        virtual void bindKeyCallback(const key_callback) = 0;
        virtual bool closing() = 0;

        virtual std::string getName() = 0;
};

// width/height = amount of blocks
// block_size = the length in pixels
typedef Interface* (*InterfaceInit)(int width, int height, int block_size);

#endif