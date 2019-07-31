#include "game.class.hpp"
#include <ranlib.h>

GameObj::GameObj() : posx(0), posy(0){} 
GameObj::GameObj(int x, int y) : posx(x), posy(y){} 
GameObj::~GameObj(){} 
GameObj::GameObj(GameObj const & obj) : posx(obj.posx), posy(obj.posy) {} 

int GameObj::getX() const {return this->posx;};
int GameObj::getY() const {return this->posy;};

void GameObj::setX(int x){ posx = x; }
void GameObj::setY(int y){ posy = y; }

void GameObj::place(Game const & map){
    int x = std::min<int>(std::max<int>((rand() & map.getW()), 1), map.getW() - 2);
    int y = std::min<int>(std::max<int>((rand() & map.getH()), 1), map.getH() - 2);
    setX(x);
    setY(y);
}

Tile::Tile(int x, int y): GameObj(x, y){};

void Tile::update(Game & map){

}
void Tile::render(Interface & i){

}


Player::Player(): direction(-1){}
Player::Player(Player const & e){}
Player::~Player(){}

void Player::update(Game & e){
    int x = 0, y = 0, X = getX(), Y = getY();

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
    X += x;
    Y += y;
    if(X < 1 || X > e.getW()-2 || Y < 1 || Y > e.getH() - 2){
        e.state = End;
        printf("Player hit wall\n");
        return;
    }
    for(std::list<Tile>::iterator I = Tiles.begin(); I != Tiles.end(); I++)
        if(I->getX() == X && I->getY() == Y){
            e.state = End;
            printf("Player hit self\n");
            return;
        } 
    setX(X);
    setY(Y);

    if(X == e.apple.getX() && Y == e.apple.getY()){
        Tiles.push_front(Tile(X, Y));
        e.apple.place(e);
        printf("Player got apple\n");
    }
    Tile tile = Tiles.back();
    Tiles.pop_back();
    tile.setX(X);
    tile.setY(Y);
    Tiles.push_front(tile);
}

void Player::render(Interface & i){
    for(std::list<Tile>::iterator q = Tiles.begin(); q != Tiles.end(); q++)
        i.drawBlock(q->getX(), q->getY(), Color(0,0,255));
}

void Player::place(Game const & map){
    int x = std::min<int>(std::max<int>((rand() & map.getW()), 3), map.getW() - 4);
    int y = std::min<int>(std::max<int>((rand() & map.getH()), 3), map.getH() - 4);
    setX(x);
    setY(y);
    Tiles.push_front(Tile(x, y));
}

int Player::getScore(){
    return Tiles.size() - 1;
}

void Apple::render(Interface & i){
    i.drawBlock(getX(), getY(), Color(255,0,0));
}

void Apple::update(Game & e){

}
