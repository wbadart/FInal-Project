// Object header file
// Object class is base class of all retrievable objects in game (bone, toy, vacuum, shampoo)

#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <pandaFramework.h>
#include <texturePool.h>

typedef std::map<std::string, std::vector<float>> confmap;

class Object {
	public:
		Object(int points_in = 0,
               std::string path_in = "",
               confmap conf = confmap());
        Object(std::string);
		~Object();

        void load(std::string p, PandaFramework *f, WindowFramework *w);
        void load_tex(std::string);

        void set_scale(float, float, float);
        void set_pos(float, float, float);
        void set_p(float);

		int getPoints();
		virtual void draw();	//draw function
	private:
		int points;
        std::string path;
        NodePath node;
};
#endif




