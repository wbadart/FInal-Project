/* Game.hpp
 *
 * Interface file for universal base class (engine); Game.
 *
 * APR 2016
 *
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <pandaFramework.h>

class Game{
    public:
        Game(int argc_in, char *argv_in[]);
        Game(int argc_in, char *argv_in[], std::string window_name_in);
        bool open_window(void);
        void load_environment(void);
    // private:
        PandaFramework framework;
        WindowFramework *window;
    private:
        std::string window_name;
};

#endif
