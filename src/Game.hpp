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
        NodePath load_model(char *model_name);
        NodePath load_model(std::string model_name);
    // private:
        PandaFramework framework;
        WindowFramework *window;
    private:
        bool window_is_open;
        std::string window_name;
};

#endif
