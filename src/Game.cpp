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

void Game::init_models(void){

    // NodePath scene = game.load_model("environment");
    // scene.reparent_to(game.window->get_render());
    // scene.set_scale(0.25f, 0.25f, 0.25f);
    // scene.set_pos(8, 22, 0);
    env = load_model("models/Maze.egg");
    PT(Texture) myTexture = TexturePool::load_texture("models/tex/wall.jpg");
    env.reparent_to(window->get_render());
    env.set_scale(10.25f, 10.25f, 10.25f);
    env.set_pos(8, 22, 0);
    env.set_texture(myTexture);

    // Load model
    pc = load_model("models/dog.egg");
    pc.set_scale(0.5);
    pc.reparent_to(window->get_render());
    window->load_model(pc, "models/dog-Anim0.egg");
}

void Game::init_keybindings(void){
	//keyboard detection
	framework.define_key("arrow_up-repeat", "move forward", move_forward, 0);
	framework.define_key("arrow_down-repeat", "move backward", move_backward, 0);
	framework.define_key("arrow_left-repeat", "move left", move_left, 0);
	framework.define_key("arrow_right-repeat", "move right", move_right, 0);
	framework.define_key("escape", "exit", esc, 0);
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

void Game::move_forward(const Event* theEvent, void* data)
{
   std:: cout << "You pressed the up arrow\n";
}

void Game::move_backward(const Event* theEvent, void* data)
{
	std::cout << "You pressed the down arrow\n";
}
void Game::move_left(const Event* theEvent, void* data)
{
	std::cout << "You pressed the left arrow\n";
}
void Game::move_right(const Event* theEvent, void* data)
{
	std::cout << "You pressed the right arrow\n";
}
void Game::esc(const Event* theEvent, void* data)
{
	std::cout << "Exit\n";
	exit(0);
}

