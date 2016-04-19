/* Game.cpp
 *
 * Implementation of engine class.
 *
 * APR 2016
 *
 */

#include "Game.hpp"

Game::Game(int argc_in, char *argv_in[]):
        Game(argc_in, argv_in, "Default window name"){};

Game::Game(int argc_in, char *argv_in[], std::string window_name_in):
        framework(), window_name(window_name_in){

    // Open framework
    framework.open_framework(argc_in, argv_in);
    framework.set_window_title(window_name);
}
