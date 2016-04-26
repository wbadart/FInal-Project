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

Object::Object(int p) {

	points = p;

}

Object::~Object() {


}

int Object::getPoints() {

	return points;
}

void Object::setPoints(int p) {

	points = p;
}

int Obeject::isCollision() {
	//collision detection stuff
	//maybe pass in an object as a parameter?
}

void Object::draw() {
	//drawing
}
#endif




