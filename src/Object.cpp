//implementation of Object class

#include "Object.hpp"

Object::Object(int p, std::string path_in, confmap conf): 
        points(p), path(path_in){
        
    if(!Game::window_is_open){}

    // data = Game::load_model(path);
    // data.reparent_to(Game::window->get_render());

    /*
    for(auto i: conf){
        switch(i->first){
            case "scale":
                data.set_scale(i->second[0],
                               i->second[1],
                               i->second[2]);
                break;
            case "pos":
                data.set_pos(i->second[0],
                             i->second[1],
                             i->second[2]);
                break;
            case "p":
                data.set_p(i->second[0]);
                break;
        }
    }
    */
}

Object::Object(std::string s):Object(0, s, confmap()){}
Object::~Object() {}

void Object::load(std::string p){
    node = Game::load_model(p);
    node.reparent_to(Game::window->get_render());
}

void Object::set_scale(float x, float y, float z){
    node.set_scale(x, y, z);
}

void Object::set_pos(float x, float y, float z){
    node.set_pos(x, y, z);
}

void Object::set_p(float d){
    node.set_p(d);
}

int Object::getPoints() {
	return points;
}

void Object::draw() {
	//drawing
}

