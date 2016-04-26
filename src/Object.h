#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
using namespace std;

class Object {

	public:
		Object(int);
		~Object();
		int getPoints();
		void setPoints(int);	//can either add or subtract points
		int isCollision();	//returns 1 if there is a collision
		virtual void draw();	//draw function
	private:
		int points;


}
#endif




