// Object header file
// Object class is base class of all retrievable objects in game (bone, toy, vacuum, shampoo)

#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
using namespace std;

class Object {

	public:
		Object(int);
		~Object();
		int getPoints();
		int isCollision();	//returns 1 if there is a collision
		virtual void draw();	//draw function
	private:
		int points;


}
#endif




