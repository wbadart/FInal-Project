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
 
// Task to move the camera
AsyncTask::DoneStatus SpinCameraTask(GenericAsyncTask* task, void* data) {
	double time = globalClock->get_real_time();
	double angledegrees = time * 6.0;
	double angleradians = angledegrees * (3.14 / 180.0);
	camera.set_pos(20*sin(angleradians),-20.0*cos(angleradians),3);
	camera.set_hpr(angledegrees, 0, 0);

	return AsyncTask::DS_cont;
}
 
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
 
  // Create the lerp intervals needed to walk back and forth
  PT(CLerpNodePathInterval) pandaPosInterval1, pandaPosInterval2,
    pandaHprInterval1, pandaHprInterval2;
  pandaPosInterval1 = new CLerpNodePathInterval("pandaPosInterval1",
    13.0, CLerpInterval::BT_no_blend,
    true, false, pandaActor, NodePath());
  pandaPosInterval1->set_start_pos(LPoint3f(0, 10, 0));
  pandaPosInterval1->set_end_pos(LPoint3f(0, -10, 0));
 
  pandaPosInterval2 = new CLerpNodePathInterval("pandaPosInterval2",
    13.0, CLerpInterval::BT_no_blend,
    true, false, pandaActor, NodePath());
  pandaPosInterval2->set_start_pos(LPoint3f(0, -10, 0));
  pandaPosInterval2->set_end_pos(LPoint3f(0, 10, 0));
 
  pandaHprInterval1 = new CLerpNodePathInterval("pandaHprInterval1", 3.0,
    CLerpInterval::BT_no_blend,
    true, false, pandaActor, NodePath());
  pandaHprInterval1->set_start_hpr(LPoint3f(0, 0, 0));
  pandaHprInterval1->set_end_hpr(LPoint3f(180, 0, 0));
 
  pandaHprInterval2 = new CLerpNodePathInterval("pandaHprInterval2", 3.0,
    CLerpInterval::BT_no_blend,
    true, false, pandaActor, NodePath());
  pandaHprInterval2->set_start_hpr(LPoint3f(180, 0, 0));
  pandaHprInterval2->set_end_hpr(LPoint3f(0, 0, 0));
 
  // Create and play the sequence that coordinates the intervals
  PT(CMetaInterval) pandaPace;
  pandaPace = new CMetaInterval("pandaPace");
  pandaPace->add_c_interval(pandaPosInterval1, 0,
    CMetaInterval::RS_previous_end);
  pandaPace->add_c_interval(pandaHprInterval1, 0,
    CMetaInterval::RS_previous_end);
  pandaPace->add_c_interval(pandaPosInterval2, 0,
    CMetaInterval::RS_previous_end);
  pandaPace->add_c_interval(pandaHprInterval2, 0,
    CMetaInterval::RS_previous_end);
  pandaPace->loop();
 
  // Add our task.
  taskMgr->add(new GenericAsyncTask("Spins the camera",
    &SpinCameraTask, (void*) NULL));
 
  // This is a simpler way to do stuff every frame,
  // if you're too lazy to create a task.
  Thread *current_thread = Thread::get_current_thread();
  int count = 0;
  while(framework.do_frame(current_thread)) {
	

	NodePath textNodePath;
	/*if(count == 0) {
		PT(TextNode) blank;
		blank = new TextNode("blank");
		blank->set_text(" ");
		NodePath textNodePath = window->get_aspect_2d().attach_new_node(blank);
	}*/

	textNodePath.detach_node();


	// TEXT
	float time = ClockObject::get_global_clock()->get_frame_time();
	int game_time = floor(time);
	std::string s1 = std::to_string(game_time);
	std::string s2 = "Time: ";
	std::string s3 = " seconds";
	s2.append(s1);
	s2.append(s3);

	/*
	COnscreenText timer("timer");
	timer.set_text(s2);
	timer.set_pos(LVecBase2f(0.95,0.95));
	timer.set_scale(0.05);
	timer.reparent_to(window->get_aspect_2d());
	return timer.generate();
	*/

	
	PT(TextNode) text;
	text = new TextNode("timer");
	text->set_text(s2);
	textNodePath = window->get_aspect_2d().attach_new_node(text);
	textNodePath.set_pos(0.95, 0, 0.90);
	textNodePath.set_scale(0.05);

	count++;
	
    // Step the interval manager
	CIntervalManager::get_global_ptr()->step();

  }
 
  framework.close_framework();
  return (0);
}
