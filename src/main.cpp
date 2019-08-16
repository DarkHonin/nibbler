#include "game.class.hpp"
int main(int ac, char** av){
    srand(time(0));
    int x = 20, y = 20;
    if (ac == 3){
        x = std::atoi(av[1]);
        x = (x >= 20 ? x: 20);
        y = std::atoi(av[2]);
        y = (y >= 20 ? y: 20);
    }
    Game game(x, y);
    game.run();
}