#include <iostream>

#include "Game.hpp"
#include "pandaFramework.h"
#include "pandaSystem.h"
#include <genericAsyncTask.h>
#include <asyncTaskManager.h>

#include <cIntervalManager.h>
#include <cLerpNodePathInterval.h>
#include <cMetaInterval.h>

// Global task manager
PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();

// Global clock
PT(ClockObject) globalClock = ClockObject::get_global_clock();

// Camera obj
NodePath camera;

AsyncTask::DoneStatus spinCameraTask(GenericAsyncTask *task, void *data){
    // calculate the new position and orientation
    double time = globalClock->get_real_time();
    double angledegrees = time * 6.;
    double angleradians = angledegrees * (3.14 / 180.);
    camera.set_pos(20*sin(angleradians), -20*cos(angleradians), 3);
    camera.set_hpr(angledegrees, 0, 0);

    return AsyncTask::DS_cont;
}
int main(int argc, char *argv[]){

    // Open window
    Game game(argc, argv);

    // Check if window opened
    if(game.open_window()){

        camera = game.window->get_camera_group();
        std::cout << "Successfully opened window\n";

        // Load models
        game.init_models();

        // Load animation
        game.window->loop_animations(0);

        // Start tasks and execute loop
        // taskMgr->add(new GenericAsyncTask("Spins the camera", &spinCameraTask, (void*) NULL));

	    //keyboard detection
	    game.framework.define_key("arrow_up-repeat", "move forward", game.move_forward, 0);
	    game.framework.define_key("arrow_down-repeat", "move backward", game.move_backward, 0);
	    game.framework.define_key("arrow_left-repeat", "move left", game.move_left, 0);
	    game.framework.define_key("arrow_right-repeat", "move right", game.move_right, 0);
	    game.framework.define_key("escape", "exit", game.esc, 0);

	    game.framework.main_loop();

    }else{
        std::cerr << "Could not load window\n";
        return 1;
    }

    //Close down
    game.framework.close_framework();
    return 0;
}
