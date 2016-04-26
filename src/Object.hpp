#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
using namespace std;

class Object {

	public:
		
		Object(int);
		~Object();
		int getPoints();		

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

#endif




