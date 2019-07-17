#ifndef DINTERFACE_H
#define DINTERFACE_H
#include <string>


class Interface{
    public:
        virtual int open_window(int width, int height) = 0;
        virtual std::string getName() = 0;
};

typedef Interface* (*InterfaceInit)(void);

#endif