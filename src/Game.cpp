/* Game.cpp
 *
 * Implementation of engine class.
 *
 * APR 2016
 *
 */

#include "Game.hpp"
#include <pandaFramework.h>
#include <collisionHandlerPusher.h>
#include <collisionNode.h>
#include <collisionSphere.h>

NodePath Game::pc = NodePath();

Game::Game(int argc_in, char *argv_in[]):
        Game(argc_in, argv_in, "Default window name"){};

Game::Game(int argc_in, char *argv_in[], std::string window_name_in):
        framework(), window_is_open(false), window_name(window_name_in){

    // Init framework and open window
    framework.open_framework(argc_in, argv_in);
    framework.set_window_title(window_name);
    open_window();
    camera = window->get_camera_group();
    camera.reparent_to(window->get_render());
    camera.set_pos(0, -3, 2);
    init_keybindings();
    init_models();
    run();
    framework.main_loop();
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
    // window->setup_trackball();
    
    window_is_open = true;
    return true;;
}

void Game::init_models(void){

    // set up enviroment, aka the maze walls
    env = load_model("models/Maze.egg");
    PT(Texture) myTexture = TexturePool::load_texture("models/tex/wall.jpg");
    env.reparent_to(window->get_render());
    env.set_scale(10.25f, 10.25f, 10.25f);
    env.set_pos(8, 22, 0);
    env.set_texture(myTexture);

    // Load model, aka the dog
    pc = load_model("models/dog.egg");
    pc.set_scale(0.5);
    pc.reparent_to(window->get_render());
    window->load_model(pc, "models/dog-Anim0.egg");

    camera.reparent_to(pc);
    camera.set_pos(18, 1, 8);
    camera.look_at(0, 0, 0);
    camera.set_p(0);

    // Load animation
    window->loop_animations(0);
}

void Game::run(void){
    PT(TextNode) text = new TextNode("timer");
    NodePath text_node;
    std::string time_string;
    float time;
    //Collision Detection
    PT(CollisionNode) cNode = new CollisionNode("cNode");
    cNode->add_solid(new CollisionSphere(0,0,0,1.0));
    NodePath pcC = pc.attach_new_node(cNode);
    pcC.show();
    cNode = new CollisionNode("cNode");
    cNode->add_solid(new CollisionSphere(0,0,0,1.0));
    NodePath envC = env.attach_new_node(cNode);
    envC.show();
    CollisionHandlerPusher pusher;
    CollisionTraverser* collTrav = new CollisionTraverser();
    collTrav->add_collider(pcC, &pusher);
    pusher.add_collider(pcC, pc);
    collTrav->add_collider(envC, &pusher);
    pusher.add_collider(envC, env);

    while(framework.do_frame(Thread::get_current_thread())){
        time = ClockObject::get_global_clock()->get_frame_time();
        time_string = "Time: " + std::to_string((int)time) + " seconds";

        text->set_text(time_string);
        text_node = window->get_aspect_2d().attach_new_node(text);
        text_node.set_pos(0.95, 0, 0.9);
        text_node.set_scale(0.05);
    
	//check collisions
	collTrav->traverse(window->get_render());
	}
}

void Game::init_keybindings(void){
	//keyboard detection for game controls: 4 arrow keys and esc
	framework.define_key("arrow_up-repeat", "move forward", move_forward, 0);
    framework.define_key("arrow_up", "move forward", move_forward, 0);
    framework.define_key("w-repeat", "move forward", move_forward, 0);
    framework.define_key("w", "move forward", move_forward, 0);

	framework.define_key("arrow_down-repeat", "move backward", move_backward, 0);
    framework.define_key("arrow_down", "move backward", move_backward, 0);
	framework.define_key("s-repeat", "move backward", move_backward, 0);
    framework.define_key("s", "move backward", move_backward, 0);

	framework.define_key("arrow_left-repeat", "move left", move_left, 0);
    framework.define_key("arrow_left", "move left", move_left, 0);
	framework.define_key("a-repeat", "move left", move_left, 0);
    framework.define_key("a", "move left", move_left, 0);

	framework.define_key("arrow_right-repeat", "move right", move_right, 0);
    framework.define_key("arrow_right", "move right", move_right, 0);
	framework.define_key("d-repeat", "move right", move_right, 0);
    framework.define_key("d", "move right", move_right, 0);

	framework.define_key("escape", "exit", esc, 0);
	framework.define_key("q", "exit", esc, 0);
}

//Wrappers to WindowFramework::load_model
NodePath Game::load_model(char *model_name){
    if(window_is_open)
        return window->load_model(framework.get_models(), model_name);
    else
        return NodePath();
}

NodePath Game::load_model(std::string model_name){
    return load_model(model_name.c_str());
}
// set player character
void Game::setpc(NodePath pc_in){
    pc = pc_in;
}
// Movement functions for the 4 arrow keys
void Game::move_forward(const Event* theEvent, void* data)
{
    PT(CLerpNodePathInterval) pandaHprInterval1;

    pandaHprInterval1 = new CLerpNodePathInterval("pandaHprInterval1", 3.0, CLerpInterval::BT_no_blend, true, false, pc, pc);
    pandaHprInterval1->set_start_pos(LPoint3f(0, 0, 0));
    pandaHprInterval1->set_end_pos(LPoint3f(-.5, 0, 0));

    PT(CMetaInterval) pandaPace;
    pandaPace = new CMetaInterval("pandaPace");
    pandaPace->add_c_interval(pandaHprInterval1, 0, CMetaInterval::RS_previous_end);
    pandaPace->start();

   //used for debugging
   std:: cout << "You pressed the up arrow\n";
}

void Game::move_backward(const Event* theEvent, void* data)
{
	std::cout << "You pressed the down arrow\n";
    PT(CLerpNodePathInterval) pandaHprInterval1;
    
    pandaHprInterval1 = new CLerpNodePathInterval("pandaHprInterval1", 3.0, CLerpInterval::BT_no_blend, true, false, pc, pc);
    pandaHprInterval1->set_start_pos(LPoint3f(0, 0, 0));
    pandaHprInterval1->set_end_pos(LPoint3f(.5, 0, 0));

    PT(CMetaInterval) pandaPace;
    pandaPace = new CMetaInterval("pandaPace");
    pandaPace->add_c_interval(pandaHprInterval1, 0, CMetaInterval::RS_previous_end);
    pandaPace->start();
}

void Game::move_left(const Event* theEvent, void* data)
{
	std::cout << "You pressed the left arrow\n";
    PT(CLerpNodePathInterval) pandaHprInterval1;
    
    pandaHprInterval1 = new CLerpNodePathInterval("pandaHprInterval1", 3.0, CLerpInterval::BT_no_blend, true, false, pc, pc);
    pandaHprInterval1->set_start_hpr(LPoint3f(0, 0, 0));
    pandaHprInterval1->set_end_hpr(LPoint3f(5, 0, 0));

    PT(CMetaInterval) pandaPace;
    pandaPace = new CMetaInterval("pandaPace");
    pandaPace->add_c_interval(pandaHprInterval1, 0, CMetaInterval::RS_previous_end);
    pandaPace->start();
}

void Game::move_right(const Event* theEvent, void* data)
{
	std::cout << "You pressed the right arrow\n";
    PT(CLerpNodePathInterval) pandaHprInterval1;
    
    pandaHprInterval1 = new CLerpNodePathInterval("pandaHprInterval1", 3.0, CLerpInterval::BT_no_blend, true, false, pc, pc);
    pandaHprInterval1->set_start_hpr(LPoint3f(0, 0, 0));
    pandaHprInterval1->set_end_hpr(LPoint3f(-5, 0, 0));

    PT(CMetaInterval) pandaPace;
    pandaPace = new CMetaInterval("pandaPace");
    pandaPace->add_c_interval(pandaHprInterval1, 0, CMetaInterval::RS_previous_end);
    pandaPace->start();
}
// hitting the esc key ends the execution
void Game::esc(const Event* theEvent, void* data)
{
    std::cout << "Exit\n";
    exit(0);
}

