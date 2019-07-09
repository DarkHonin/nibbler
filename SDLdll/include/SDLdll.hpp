#ifndef SDLDLL_H
#define SDLDLL_H

#include <string>

class SDLDll{
    public:
        SDLDll(void);
        std::string getName(void);
};

#pragma export(SDLDll::getName)

#endif