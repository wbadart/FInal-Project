#include <iostream>

#include "Game.h"
#include "Game.cpp"
#include "pandaFramework.h"
#include "pandaSystem.h"
#include <genericAsyncTask.h>
#include <asyncTaskManager.h>

#include <cIntervalManager.h>
#include <cLerpNodePathInterval.h>
#include <cMetaInterval.h>
#include <texturePool.h>

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
//temporary move functions
//void KeyPressed(string Key)
//{
//	switch (Key)
//	{
//		case "arrow_up":
//			break;
//		case "arrow_down":
//			break;
//		case "arrow_left":
//			break;
//		case "arrow_right":
//			break;
//		case "escape":
//			break;
//	}
//}
//called when up arrow is pressed
/**
void move_forward(const Event * theEvent, void * data)
{
	std::cout << "up arrow pressed" << std::endl;
}
//called when down arrow is pressed
void move_backward(const Event * theEvent, void * data)
{
        std::cout << "down arrow pressed" << std::endl;
}
//called when left arrow is pressed
void move_left(const Event * theEvent, void * data)
{
        std::cout << "left arrow pressed" << std::endl;
}
//called when right arrow is pressed
void move_right(const Event * theEvent, void * data)
{
        std::cout << "right arrow pressed" << std::endl;
}
//called when esc is pressed, causes window to close
void esc(const Event * theEvent, void * data)
{
	exit(0);
}
**/
int main(int argc, char *argv[]){

    // Open window
    Game game(argc, argv);

    // Check if window opened
    if(game.open_window()){

        camera = game.window->get_camera_group();
        std::cout << "Successfully opened window\n";

        // Load environment
        NodePath maze = game.load_model("models/Maze.egg");
        maze.reparent_to(game.window->get_render());
        maze.set_scale(10.25f, 10.25f, 10.25f);
        maze.set_pos(8, 22, 0);

        //game.framework.define_key("w", "w_move_forward", auto [](Event *e, void *d){
        //std::cout << "YOU PRESSED W!!!!\n";});

        // Load environment
        // NodePath scene = game.load_model("environment");
        // scene.reparent_to(game.window->get_render());
        // scene.set_scale(0.25f, 0.25f, 0.25f);
        // scene.set_pos(8, 22, 0);
        NodePath scene = game.load_model("models/Maze.egg");
        PT(Texture) myTexture = TexturePool::load_texture("models/tex/wall.jpg");
        scene.reparent_to(game.window->get_render());
        scene.set_scale(10.25f, 10.25f, 10.25f);
        scene.set_pos(8, 22, 0);
        scene.set_texture(myTexture);

        // Load model
        NodePath pandaActor = game.load_model("models/dog.egg");
        pandaActor.set_scale(0.5);
        pandaActor.reparent_to(game.window->get_render());

        // Load animation
        game.window->load_model(pandaActor, "models/dog-Anim0.egg");
        game.window->loop_animations(0);

        // Create lerp intervals needed to walk back and forth
        /*PT(CLerpNodePathInterval) pandaPosInterval1, pandaPosInterval2,
            pandaHprInterval1, pandaHprInterval2;

        pandaPosInterval1 = new CLerpNodePathInterval("pandaPosInterval1",
                13.0, CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
        pandaPosInterval1->set_start_pos(LPoint3f(0, 10, 0));
        pandaPosInterval1->set_end_pos(LPoint3f(0, -10, 0));
    
        pandaPosInterval2 = new CLerpNodePathInterval("pandaPosInterval2",
                13.0, CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
        pandaPosInterval2->set_start_pos(LPoint3f(0, -10, 0));
        pandaPosInterval2->set_end_pos(LPoint3f(0, 10, 0));

        pandaHprInterval1 = new CLerpNodePathInterval("pandaHprInterval1", 3.,
                CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
        pandaHprInterval1->set_start_hpr(LPoint3f(0, 0, 0));
        pandaHprInterval1->set_end_hpr(LPoint3f(180, 0, 0));

        pandaHprInterval2 = new CLerpNodePathInterval("pandaHptInterval2", 3.,
                CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
        pandaHprInterval2->set_start_hpr(LPoint3f(180, 0, 0));
        pandaHprInterval2->set_end_hpr(LPoint3f(0, 0, 0));

        // Create and play the sequence of intervals
        PT(CMetaInterval) pandaPace;;
        pandaPace = new CMetaInterval("pandaPace");
        pandaPace->add_c_interval(pandaPosInterval1, 0, CMetaInterval::RS_previous_end);
        pandaPace->add_c_interval(pandaPosInterval2, 0, CMetaInterval::RS_previous_end);
        pandaPace->add_c_interval(pandaHprInterval1, 0, CMetaInterval::RS_previous_end);
        pandaPace->add_c_interval(pandaHprInterval2, 0, CMetaInterval::RS_previous_end);

        pandaPace->loop(); */


        // Start tasks and execute loop
        // taskMgr->add(new GenericAsyncTask("Spins the camera", &spinCameraTask, (void*) NULL));

	//keyboard detection
	game.framework.define_key("arrow_up", "move forward", move_forward, 0);
	game.framework.define_key("arrow_down", "move backward", move_backward, 0);
	game.framework.define_key("arrow_left", "move left", move_left, 0);
	game.framework.define_key("arrow_right", "move right", move_right, 0);
	game.framework.define_key("escape", "exit", esc, 0);

	game.framework.main_loop();
    }else{
        std::cerr << "Could not load window\n";
        return 1;
    }

    //Close down
    game.framework.close_framework();
    return 0;
}
