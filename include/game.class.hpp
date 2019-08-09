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
#define NCUR "NCUR"

#define BLOCK 15

class Game;

enum GameState{
    Start, Pause, Running, End, Switching
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
        void handleKey(int key);


    private:
        int posx;
        int posy;
};

class Tile{
    public:
        Tile(int x, int y);
        ~Tile();
        void update(Game & map);
        void render(Interface & i);
        int x;
        int y;
    private:
};

class Player : public GameObj{
    public:
        Player();
        Player(Player const & e);
        ~Player();

        void update(Game & map);
        void render(Interface & i);
        void place(Game const & map);
        void handleKey(int key);
        void reset(Game const & map);
        int getScore();
        
    private:
        std::list<Tile> Tiles;
        bool DirChanged;
        int direction;
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

        void update();
        void render();

        void loadDll(std::string const path = GLFW);
        void run();

        int getW() const;
        int getH() const;
        void doNoting();
        
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