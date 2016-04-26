#include <iostream>

#include "Game.hpp"
#include "pandaFramework.h"
#include "pandaSystem.h"
#include <genericAsyncTask.h>
#include <asyncTaskManager.h>

#include <cIntervalManager.h>
#include <cLerpNodePathInterval.h>
#include <cMetaInterval.h>

// Global clock
PT(ClockObject) globalClock = ClockObject::get_global_clock();

// Camera obj
NodePath camera;

int main(int argc, char *argv[]){

    // Open window
    Game game(argc, argv);

    // Check if window opened
    if(game.open_window()){

        camera = game.window->get_camera_group();
        std::cout << "Successfully opened window\n";

        // Load models
        game.init_models();

        // Setup controls
        game.init_keybindings();

        // Start tasks and execute loop
	    game.framework.main_loop();

    }else{
        std::cerr << "Could not load window\n";
        return 1;
    }

    //Close down
    game.framework.close_framework();
    return 0;
}
