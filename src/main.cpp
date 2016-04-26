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

    //Close down
    game.framework.close_framework();
    return 0;
}
