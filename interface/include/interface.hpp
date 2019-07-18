#ifndef DINTERFACE_H
#define DINTERFACE_H
#include <string>
#include <iostream>

class InterfaceException : public std::exception{};

typedef void (*key_callback)(int key, int scancode, int mods);

class Interface{
    public:

        virtual int open_window(int width, int height) = 0;

        virtual void drawBorder() = 0;
        virtual void updateView() = 0;

        virtual void bindKeyCallback(const key_callback) = 0;
        virtual bool closing() = 0;

        virtual std::string getName() = 0;
};

typedef Interface* (*InterfaceInit)(void);

#endif