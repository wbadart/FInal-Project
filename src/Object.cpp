//implementation of Object class

#include "Object.h"

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

