#ifndef NCUR_INTERFACE_H
#define NCUR_INTERFACE_H

#include "interface.hpp"
#include <ncurses.h>

class NCUR : public Interface{
    public:
        NCUR(int x, int y, int b);
        NCUR(NCUR const & obj);
        ~NCUR();

        void drawBlock(int x, int y, Color c);
        void drawText(int x, int y, std::string const txt);

        void prerender();
        void postrender();

        void bindKeyCallback(const key_callback);
        bool closing();

        void close();
        void pollEvents();
        std::string getName();
    private:
        int x;
        int y;
        int b;
};

extern "C"{
    Interface * Interface_Init(int w, int h, int b){
        return new NCUR(w, h, b);
    }
}

#endif