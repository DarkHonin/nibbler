#ifndef SFML_INTERFACE_H
#define SFML_INTERFACE_H

#include "interface.hpp"
#include <SFML/Window.hpp>

class SFML : public Interface{
    public:
        SFML();
        SFML(SFML const & obj);
        ~SFML();

        int open_window(int width, int height);
        std::string getName();
    private:
        sf::Window *_window;
};

#endif