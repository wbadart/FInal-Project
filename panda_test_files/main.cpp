#include <iostream>

#include <pandaFramework.h>
#include <pandaSystem.h>
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
    PandaFramework framework;
    framework.open_framework(argc, argv);
    framework.set_window_title("My window");
    WindowFramework *window = framework.open_window();

    camera = window->get_camera_group();

    // Enable keyboard and camera movement
    window->enable_keyboard();
    window->setup_trackball();

    // Check if window opened
    if(window != (WindowFramework *) NULL){
        std::cout << "Successfully openend window\n";

        // Load environment
        NodePath scene = window->load_model(framework.get_models(), "environment");
        scene.reparent_to(window->get_render());
        scene.set_scale(0.25f, 0.25f, 0.25f);
        scene.set_pos(-8, 42, 0);

        // Load model
        NodePath pandaActor = window->load_model(framework.get_models(), "panda-model");
        pandaActor.set_scale(0.005);
        pandaActor.reparent_to(window->get_render());

        // Load animation
        window->load_model(pandaActor, "panda-walk4");
        window->loop_animations(0);

        // Create lerp intervals needed to walk back and forth
        PT(CLerpNodePathInterval) pandaPosInterval1, pandaPosInterval2,
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

        pandaPace->loop();


        // Start tasks and execute loop
        taskMgr->add(new GenericAsyncTask("Spins the camera", &spinCameraTask, (void*) NULL));

        framework.main_loop();

    }else{
        std::cerr << "Could not load window\n";
        return 1;
    }

    //Close down
    framework.close_framework();
    return 0;
}
