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
#include <pandaFramework.h>

class Game{
    public:
        Game(int argc_in, char *argv_in[]);
        Game(int argc_in, char *argv_in[], std::string window_name_in);
    // private:
        PandaFramework framework;
        WindowFramework *window;
    private:
        std::string window_name;
};

#endif
