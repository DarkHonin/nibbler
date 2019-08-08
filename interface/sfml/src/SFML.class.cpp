#include "SFML.class.hpp"

SFML::SFML(int x, int y, int b) : _xBlocks(x), _yBlocks(y), _blockSize(b){
    _window = window(sf::VideoMode(x * b, y * b), getName());
}

SFML::SFML(SFML const & obj) : _window(obj._window){}

SFML::~SFML(){}

void SFML::drawBlock(int x, int y, Color c);
void SFML::drawText(int x, int y, std::string const txt);

void SFML::prerender();
void SFML::postrender();

void SFML::bindKeyCallback(const key_callback);
bool SFML::closing();

void SFML::close();

std::string SFML::getName(){
    return std::string("SFMLibbler");
}