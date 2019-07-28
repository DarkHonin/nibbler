#include "game.class.hpp"
#include <ranlib.h>

GameObj::GameObj() : posx(0), posy(0){} 
GameObj::~GameObj(){} 
GameObj::GameObj(GameObj const & obj) : posx(obj.posx), posy(obj.posy) {} 

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

Tile::Tile(int x, int y): x(x), y(y) {}
Tile::Tile(Tile const & obj) : Tile(obj.x, obj.y){}
Tile::~Tile(){}

Player::Player(){}
Player::Player(Player const & e){}
Player::~Player(){}
void Player::update(GameMap & e){
    int x = getX();
    int y = getY();
    switch(direction){
        case 0: // Up
            y++;
            break;
        case 1: // Left
            x--;
            break;
        case 2: // Down
            y--;
            break;
        case 3: // Right
            x++;
            break;
    }
    if(x < 1 || x > e.getW()-2 || y < 1 || y > e.getH() - 2){
        printf("Dies here");
        return;
    }
    
    Tile back = Tiles[Tiles.size()];
    Tile Front = Tiles[0];
    Tiles[0] = back;
    Tiles[Tiles.size()] = Front;
    Tiles[0].x = x;
    Tiles[0].y = y;
    setX(x);
    setY(y);
}

void Player::render(Interface & i){
    for(std::vector<Tile>::iterator q = Tiles.begin(); q != Tiles.end(); q++)
        i.drawBlock((*q).x, (*q).y, Color(255,255,0));
}

void Player::place(GameMap const & map){
    int x = std::min<int>(std::max<int>((rand() & map.getW()), 3), map.getW() - 4);
    int y = std::min<int>(std::max<int>((rand() & map.getH()), 3), map.getH() - 4);
    setX(x);
    setY(y);
    Tiles.push_back(Tile(x, y));
}

void Apple::render(Interface & i){
    i.drawBlock(getX(), getY(), Color(255,0,0));
}

void Apple::update(GameMap & e){

}
