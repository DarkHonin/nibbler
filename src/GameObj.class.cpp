#include "game.class.hpp"
#include <ranlib.h>

GameObj::GameObj() : posx(0), posy(0), placed(false){} 
GameObj::~GameObj(){} 
GameObj::GameObj(GameObj const & obj) : posx(obj.posx), posy(obj.posy), placed(obj.placed){} 

int GameObj::getX() const {return this->posx;};
int GameObj::getY() const {return this->posy;};

void GameObj::setX(int x){ posx = x; }
void GameObj::setY(int y){ posy = y; }

void GameObj::place(GameMap const & map){
    int x = std::min<int>(std::max<int>((rand() & map.getW()), 1), map.getW() - 2);
    int y = std::min<int>(std::max<int>((rand() & map.getH()), 1), map.getH() - 2);
    setX(x);
    setY(y);
}


Player::Player(){}
Player::Player(Player const & e){}
Player::~Player(){}
void Player::update(GameMap & e){

}

void Player::render(Interface & i){
    i.drawBlock(getX(), getY(), Color(255,255,0));
}

void Player::place(GameMap const & map){
    int x = std::min<int>(std::max<int>((rand() & map.getW()), 3), map.getW() - 4);
    int y = std::min<int>(std::max<int>((rand() & map.getH()), 3), map.getH() - 4);
    setX(x);
    setY(y);
    // ToDo make direction
    if(x > map.getW() / 2 && y > map.getH() / 2)
        direction = 2;
    if(x < map.getW() / 2 && y < map.getH() / 2)
        direction = 0;
}

void Apple::render(Interface & i){
    i.drawBlock(getX(), getY(), Color(255,0,0));
}

void Apple::update(GameMap & e){

}
