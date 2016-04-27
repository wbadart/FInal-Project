// driver program for Game engine

#include "Game.hpp"

int main(int argc, char *argv[]){

    // Open window
    Game game(argc, argv);
    game.run();
    
    return 0;
}
