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
#include <collisionTube.h>

NodePath Game::pc = NodePath();
NodePath Game::camera = NodePath();
int      Game::OTS_enabled = 0;
bool     Game::window_is_open = false;
WindowFramework *Game::window;
PandaFramework   Game::framework;

std::vector<CMetaInterval*> Game::intervals = std::vector<CMetaInterval*>();

Game::Game(int argc_in, char *argv_in[]):
        Game(argc_in, argv_in, "Default window name"){};

Game::Game(int argc_in, char *argv_in[], std::string window_name_in):
        window_name(window_name_in), score(0){

    // Init framework and open window
    
    jung = new Object();
    maze = new Object();

    framework.open_framework(argc_in, argv_in);
    framework.set_window_title(window_name);
    open_window();
    init_keybindings();
    init_models();
}

Game::~Game(){
    framework.close_framework();

    for(auto it = intervals.begin(); it != intervals.end(); it++)
        delete *it;
}

bool Game::open_window(void){
    
    // Point le pointer
    window = framework.open_window();
    if(window == (WindowFramework *) NULL){
        std::cerr << "Unable to open window.\n";
        return false;
    }

    // Enable keyboard and camera control
    window->enable_keyboard();
    
    camera = window->get_camera_group();
    window_is_open = true;
    return true;
}

void Game::init_models(void){

    // set up mazeiroment, aka the maze walls
    maze->load("models/Maze.egg", &framework, window);
    maze->load_tex("models/tex/wall.png");
    maze->set_scale(10.25f, 10.25f, 10.25f);
    maze->set_pos(8, 22, 0);

    // test object pointer
    jung->load("environment", &framework, window);
    jung->set_scale(2, 2, 2);
    jung->set_pos(8, 12, -0.38);

    gen_objects();

    // Load model, aka the dog
    pc = load_model("models/dog.egg");
    pc.set_scale(0.5);
    pc.reparent_to(window->get_render());
    window->load_model(pc, "models/dog-Anim0.egg");

//    while(framework.do_frame(current_thread))
//    {
	//check collisions
//    }
    camera.reparent_to(pc);
    camera.set_pos(18, 1, 8);
    camera.look_at(0, 0, 0);
    camera.set_p(0);

    // Load animation
    window->loop_animations(0);
}

void Game::gen_objects(void){
    int num_objs = rand() % 6 + 2, i = 0, j = 0;
    for(i = 0; i < num_objs * 2; i++){
        objs.push_back(new Bone);
        objs[i]->load("models/bone.egg", &framework, window);
        objs[i]->set_scale(0.35);
        objs[i]->set_pos(rand() % 24, rand() % 24, 2);
        objs[i]->set_p((rand() % 45) + 15);

        i++;
        
        objs.push_back(new Shampoo);
        objs[i]->load("models/shampoo.egg", &framework, window);
        objs[i]->set_scale(0.15);
        objs[i]->set_pos(rand() % 24, rand() % 24, 2);
        objs[i]->set_p((rand() % 45) + 15);
    }
}

void Game::run(void){
    PT(TextNode) text = new TextNode("timer");
    NodePath text_node;
    std::string msg;
    float time;
    //Collision Detection
    CollisionTraverser* collTrav = new CollisionTraverser();
    CollisionHandlerPusher pusher;
    CollisionNode* cNode = new CollisionNode("cNode");
    cNode->add_solid(new CollisionSphere(0,0,0,1.0));
    cNode->add_solid(new CollisionSphere(5,0,0,1.0));
    //CollisionTube(LPoint3f(5, 0, 0), LPoint3f(-1, 0, 0), 2.0));
    NodePath pcC = pc.attach_new_node(cNode);
    pcC.show();
    cNode = new CollisionNode("cNode");
    cNode->add_solid(new CollisionBox(LPoint3f(0, 2.9, 0), 3, 0.05 , 1.0)); //a
    cNode->add_solid(new CollisionBox(LPoint3f(2.95, 0, 0), 0.05, 3 , 1.0)); //b
    cNode->add_solid(new CollisionBox(LPoint3f(0, -2.95, 0), 3, 0.05 , 1.0)); //c
    cNode->add_solid(new CollisionBox(LPoint3f(-2.95, 0, 0), 0.05, 3 , 1.0)); //d
    cNode->add_solid(new CollisionBox(LPoint3f(-2.0, 1.5, 0), 0.06, 0.5, 1.0)); //e
    cNode->add_solid(new CollisionBox(LPoint3f(0, 2.0, 0), 2, 0.06 , 1.0)); //f
    cNode->add_solid(new CollisionBox(LPoint3f(2.0, 0.6, 0), 0.06, 1.5 , 1.0)); //g
    cNode->add_solid(new CollisionBox(LPoint3f(0.60, -0.1, 0), 0.5, 0.06 , 1.0)); //h
    NodePath mazeC = maze->node.attach_new_node(cNode);
    mazeC.show();
    pusher.add_collider(pcC, pc);
    collTrav->add_collider(pcC, &pusher);
    //Thread *current_thread = Thread::get_current_thread();

    while(framework.do_frame(Thread::get_current_thread())){
        time = ClockObject::get_global_clock()->get_frame_time();
        msg = "Time: " + std::to_string((int)time) + " seconds\nScore: " + std::to_string(score);
        text->set_text(msg);
        text_node = window->get_aspect_2d().attach_new_node(text);
        text_node.set_pos(0.95, 0, 0.9);
        text_node.set_scale(0.05);
        collTrav->traverse(window->get_render());
    }
}

//Wrappers to WindowFramework::load_model
NodePath Game::load_model(std::string model_name){
    if(window_is_open)
        return window->load_model(framework.get_models(), model_name.c_str());
    else
        return NodePath();
}

//keyboard detection for game controls: 4 arrow keys and esc
void Game::init_keybindings(void){
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

    framework.define_key("o", "toggle cam", toggle_cam, 0);
}

// Cycle through OTS->bird's eye->FP
void Game::toggle_cam(const Event* e, void *d){
    std::cout << "Entering POV: " << OTS_enabled << std::endl;
    switch(OTS_enabled){
        case 0: // OTS -> bird's eye
            camera.set_pos(10, 1, 300);
            camera.look_at(0, 0, 0);
            break;
        case 1: // bird's eye -> FP
            camera.set_pos(2.1, 0, 7.6);
            camera.set_p(0);
            break;
        case 2: // FP -> OTS
            camera.set_pos(18, 1, 8);
            camera.look_at(0, 0, 0);
            camera.set_p(0);
    }
    OTS_enabled = (OTS_enabled + 1) % 3;
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

    intervals.push_back(pandaPace);

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

    intervals.push_back(pandaPace);
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

    intervals.push_back(pandaPace);
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

    intervals.push_back(pandaPace);
}
// hitting the esc key ends the execution
void Game::esc(const Event* theEvent, void* data)
{
    std::cout << "Exit\n";
    exit(0);
}

