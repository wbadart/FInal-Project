/* Game.hpp
 *
 * Interface file for universal base class (engine); Game.
 *
 * APR 2016
 *
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

// Panda framework should exist on CPATH or use gcc -I...
// Or just use the makefile (be sure PANDA_CPATH and PANDA_LIB
// environment variables are up to date for this)
#include <pandaFramework.h>
#include <texturePool.h>
#include <cIntervalManager.h>
#include <cLerpNodePathInterval.h>
#include <cMetaInterval.h>
#include "collisionHandlerPusher.h"
#include "collisionNode.h"
#include "collisionSphere.h"
#include "modelPool.h"

#include "Object.hpp"
class Object;
#include "Bone.hpp"

class Game{

    friend class Object;

    public:

        // Primary constructor; able to use command line arguments
        Game(int argc_in, char *argv_in[]);

        // Overloaded constructor which automatically names window
        Game(int argc_in, char *argv_in[], std::string window_name_in);

        // Deconstructor
        ~Game();

        // Wrapper to PandaFramework::openwindow(); includes failure check
        bool open_window(void);

        // Load models into window once it's opened
        void init_models(void);

        // Setup keybindings
        void init_keybindings(void);

        // Wrapper to PandaFramework::main_loop
        void run(void);

        // Wrappers to WindowFramework::load_model
        static NodePath load_model(std::string model_name);

        // Frequently accessed data members; much more efficient to make
        // public, at least for the time being
        static PandaFramework framework;
        static WindowFramework *window;
	
        // Move the player character 
	    static void move_forward(const Event*, void*);
	    static void move_backward(const Event*, void*);
	    static void move_left(const Event*, void*);
	    static void move_right(const Event*, void*);

	    // triggered when esc key is pressed, ends execution
        static void esc(const Event*, void*);

        // toggle OTS and bird's eye POV
        static void toggle_cam(const Event*, void*);

    private:
        
        // Tracks the current POV
        static int OTS_enabled;

        // Tracks whether Game::open_window() has been called
        static bool window_is_open;

        // Stores the name of the window
        std::string window_name;

        // Stores the player character object. Will be converted to
        // our object class down the line
        static NodePath pc;

        // Store the environment nodepath
        Object *maze;
        Object *jung;
        static NodePath camera;
        std::vector<Object*> objs;

        int curRot;

        // Track allocated inervals
        static std::vector<CMetaInterval*> intervals;
};

#endif
