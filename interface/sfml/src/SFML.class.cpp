#include "SFML.class.hpp"

SFML::SFML(){}

SFML::SFML(SFML const & obj) : _window(obj._window){}

SFML::~SFML(){}

int SFML::open_window(int width, int height){
    this->_window = new sf::Window(sf::VideoMode(width, height), this->getName());
    return 1;
}

void SFML::drawBorder(){}
void SFML::updateView(){}

std::string SFML::getName(){
    return std::string("SFMLibbler");
}