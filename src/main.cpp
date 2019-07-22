#include "game.class.hpp"

int main(int ac, char** av){
    int x = 20, y = 20;
    if (ac == 3){
        x = std::atoi(av[1]);
        y = std::atoi(av[2]);
    }
    Game game(x, y);
    game.loadDll();
    game.run();
}