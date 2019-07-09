#ifndef SFMLDLL_H
#define SFMLDLL_H

#include <string>

class SFMLDll{
    public:
        SFMLDll(void);
        std::string getName(void);
};

#pragma export(SFMLDll::getName)

#endif