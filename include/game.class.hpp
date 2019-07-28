#ifndef NIBBLER_H
#define NIBBLER_H

#include "interface.hpp"
#include <map>
#include <string>
#include <iostream>
#include <dlfcn.h>
#include <vector>
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

class GameMap{
    public:
        GameMap(int w, int h);
        GameMap(GameMap const & obj);
        ~GameMap();

        int getW() const;
        int getH() const;

    private:
        int w;
        int h;
};

class GameObj{
    public:
        GameObj();
        GameObj(GameObj const & obj);
        ~GameObj();

        int getX() const;
        int getY() const;
        void setX(int x);
        void setY(int y);
        void place(GameMap const & map);

        virtual void update(GameMap & map) = 0;
        virtual void render(Interface & i) = 0;


    private:
        int posx;
        int posy;
};

class Tile{
    public:
        Tile(int x, int y);
        Tile(Tile const & obj);
        ~Tile();
    
        int x;
        int y;
};

class Player : public GameObj{
    public:
        Player();
        Player(Player const & e);
        ~Player();

        void update(GameMap & map);
        void render(Interface & i);
        void place(GameMap const & map);
        
        int direction;
    private:
        std::vector<Tile> Tiles;
};

class Apple : public GameObj{
    public:
        void update(GameMap & map);
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
        
        GameMap map;
        Player player;
        Apple apple;
        GameState state;
    private:
        void *interface;
        Interface *interface_instance;
};

#endif