#ifndef NIBBLER_H
#define NIBBLER_H

#include "interface.hpp"
#include <map>
#include <string>
#include <iostream>
#include <dlfcn.h>
#include <list>
#include <cstdlib>
#include <ctime>

#define SDL "SDL"
#define GLFW "GLFW"
#define SFML "SFML"

#define BLOCK 15

class Game;

enum GameState{
    Start, Pause, Running, End
};

class GameObj{
    public:
        GameObj();
        GameObj(GameObj const & obj);
        GameObj(int x, int y);
        ~GameObj();

        int getX() const;
        int getY() const;
        void setX(int x);
        void setY(int y);
        void place(Game const & map);

        virtual void update(Game & map) = 0;
        virtual void render(Interface & i) = 0;


    private:
        int posx;
        int posy;
};

class Tile : public GameObj{
    public:
        Tile(int x, int y);
        void update(Game & map);
        void render(Interface & i);

};

class Player : public GameObj{
    public:
        Player();
        Player(Player const & e);
        ~Player();

        void update(Game & map);
        void render(Interface & i);
        void place(Game const & map);
        int getScore();
        
        int direction;
    private:
        std::list<Tile> Tiles;
};

class Apple : public GameObj{
    public:
        void update(Game & map);
        void render(Interface & i);
};


class Game{
    public:
        std::map<std::string, std::string> DLLS;
        Game(int w, int h);
        Game(Game & obj);
        ~Game();

        void update(int delta);
        void render(int delta);

        void loadDll(std::string const path = GLFW);
        void run();

        int getW() const;
        int getH() const;
        
        Player player;
        Apple apple;
        GameState state;
    private:
        void *interface;
        Interface *interface_instance;
        int w;
        int h;
};

#endif