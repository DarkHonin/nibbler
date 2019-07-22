#include "game.class.hpp"

GameObj::GameObj() : posx(0), posy(0), placed(false){} 
GameObj::~GameObj(){} 
GameObj::GameObj(GameObj const & obj) : posx(obj.posx), posy(obj.posy), placed(obj.placed){} 

int GameObj::getX() const {return this->posx;};
int GameObj::getY() const {return this->posy;};





Player::Player(){}
Player::Player(Player const & e){}
Player::~Player(){}
void Player::update(GameMap & e){

}

void Player::render(Interface & i){

}

void Apple::render(Interface & i){
    i.drawBlock(this->getX(), this->getY(), RED);
}

void Apple::update(GameMap & e){

}