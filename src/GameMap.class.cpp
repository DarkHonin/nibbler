#include "game.class.hpp"

GameMap::GameMap(int w, int h) : w(w), h(h){}

GameMap::GameMap(GameMap const & obj) : w(obj.w), h(obj.h){}
GameMap::~GameMap(){}

int GameMap::getW() const{ return this->w; }
int GameMap::getH() const{ return this->h; }
