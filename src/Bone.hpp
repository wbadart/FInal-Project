// Bone objects can be collected by the dog to add points to your score
// Bone inherits from the Object class

#ifndef BONE_H
#define BONE_H

#include "Object.hpp"
class Object;

class Bone: public Object {

	public:
        void load(std::string p, PandaFramework *f,
                WindowFramework *w);
	private:
        

};

#endif
