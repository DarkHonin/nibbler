#ifndef SFML_INTERFACE_H
#define SFML_INTERFACE_H

#include "interface.hpp"
#include <SFML/Window.hpp>

class SFML : public Interface{
    public:
        SFML(int x, int y, int b);
        SFML(SFML const & obj);
        ~SFML();

        void drawBlock(int x, int y, Color c);
        void drawText(int x, int y, std::string const txt);

        void prerender();
        void postrender();

        void bindKeyCallback(const key_callback);
        bool closing();

        void close();
        

        std::string getName();
    private:
        sf::Window *_window;
        int _xBlocks;
        int _yBlocks;
        int _blockSize;
};

#endif