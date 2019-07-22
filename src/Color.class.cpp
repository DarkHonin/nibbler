#include "game.class.hpp"

Color::Color(char r, char g, char b)    : r(r), g(g), b(b){};
Color::Color(Color const & o)           : Color(o.r, o.g, o.b){};
Color::Color()                          : Color(0,0,0){}
Color::~Color(){}

void Color::apply(Color e){
    this->r = e.r;
    this->g = e.r;
    this->b = e.r;
};