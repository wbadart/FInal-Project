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
        framework(), window_is_open(false), window_name(window_name_in){

    // Init framework and open window
    framework.open_framework(argc_in, argv_in);
    framework.set_window_title(window_name);
    
}

bool Game::open_window(void){
    
    // Point le pointer
    window = framework.open_window();
    if(window == (WindowFramework *) NULL){
        std::cerr << "Unable to open window.\n";
        return false;;
    }

    // Enable keyboard and camera control
    window->enable_keyboard();
    window->setup_trackball();
    
    window_is_open = true;
    return true;;
}

NodePath Game::load_model(char *model_name){
    if(window_is_open)
        return window->load_model(framework.get_models(), model_name);
    else
        return NodePath();
}

NodePath Game::load_model(std::string model_name){
    return load_model(model_name.c_str());
}

void Game::setpc(NodePath pc_in){
    pc = pc_in;
}

void Game::move_model_forward(const Event *e, void *dataptr){
    std:: cout << "YOU PRESSED W!!!\n";
}
