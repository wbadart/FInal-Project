#include "pandaFramework.h"
#include "pandaSystem.h"
 
#include "genericAsyncTask.h"
#include "asyncTaskManager.h"
 
#include "cIntervalManager.h"
#include "cLerpNodePathInterval.h"
#include "cMetaInterval.h"

// #include "cOnscreenText.h"

 
// Global stuff
PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr(); 
PT(ClockObject) globalClock = ClockObject::get_global_clock();
NodePath camera;
 
int main(int argc, char *argv[]) {
    // Open a new window framework and set the title
    PandaFramework framework;
    framework.open_framework(argc, argv);
    framework.set_window_title("My Panda3D Window");
 
    // Open the window
    WindowFramework *window = framework.open_window();
    camera = window->get_camera_group(); // Get the camera and store it
 
    // Load the environment model
    NodePath scene = window->load_model(framework.get_models(),
      "environment");
    scene.reparent_to(window->get_render());
    scene.set_scale(0.25 , 0.25, 0.25);
    scene.set_pos(-8, 42, 0);
 
    // Load our panda
    NodePath pandaActor = window->load_model(framework.get_models(),
      "panda-model");
    pandaActor.set_scale(0.005);
    pandaActor.reparent_to(window->get_render());
 
    // Load the walk animation
    window->load_model(pandaActor, "panda-walk4");
    window->loop_animations(0);
 
    // This is a simpler way to do stuff every frame,
    // if you're too lazy to create a task.
    Thread *current_thread = Thread::get_current_thread();
    NodePath textNodePath;
    std::string time_string;
    PT(TextNode) text = new TextNode("timer");
    float time;

    while(framework.do_frame(current_thread)) {

        // TEXT
        time = ClockObject::get_global_clock()->get_frame_time();
        time_string = "Time: " + std::to_string((int)time) + " s";
        
        text->set_text(time_string);
        textNodePath = window->get_aspect_2d().attach_new_node(text);
        textNodePath.set_pos(0.95, 0, 0.90);
        textNodePath.set_scale(0.05);

        // Step the interval manager
        CIntervalManager::get_global_ptr()->step();

    }

    delete text;
 
    framework.close_framework();
    return (0);
}
