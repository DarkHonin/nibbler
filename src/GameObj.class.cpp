#include "game.class.hpp"
#include <ranlib.h>

GameObj::GameObj() : posx(0), posy(0){} 
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

Tile::Tile(int d): direction(d), c(0) {}
Tile::Tile(Tile const & obj) : direction(obj.direction){}
Tile::~Tile(){}


Player::Player(): direction(-1){}
Player::Player(Player const & e){}
Player::~Player(){}

void Player::update(Game & e){
    int x = 0, y = 0, X = getX(), Y = getY();

    Tiles.front().direction = direction;
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
        return;
    }
    setX(X);
    setY(Y);
    
    Tile last = Tiles.back();
    Tiles.pop_back();
    last.direction = direction;
    Tiles.push_front(last);

    if(X == e.apple.getX() && Y == e.apple.getY()){
        Tile nt = Tile(direction);
        Tiles.push_back(nt);
        e.apple.place(e);
    }
}

void Player::render(Interface & i){
    int x = 0;
    int y = 0;
    for(std::list<Tile>::iterator q = Tiles.begin(); q != Tiles.end(); q++){
        switch(q->direction){
            case 0: y -= 1; break;
            case 1: x += 1; break;
            case 2: y += 1; break;
            case 3: x -= 1; break;
        }
        i.drawBlock(getX() + x, getY() + y, Color(255,0,255));
    }
    i.drawBlock(getX(), getY(), Color(255,255,0));
}

void Player::place(Game const & map){
    int x = std::min<int>(std::max<int>((rand() & map.getW()), 3), map.getW() - 4);
    int y = std::min<int>(std::max<int>((rand() & map.getH()), 3), map.getH() - 4);
    setX(x);
    setY(y);
    Tiles.push_front(Tile(direction));
}

void Apple::render(Interface & i){
    i.drawBlock(getX(), getY(), Color(255,0,0));
}

void Apple::update(Game & e){

}
