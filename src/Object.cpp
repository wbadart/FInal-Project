//implementation of Object class

#include "Object.hpp"

Object::Object(int p, std::string path_in, confmap conf): 
        points(p), path(path_in){
}

Object::Object(std::string s):Object(0, s, confmap()){}
Object::~Object() {}

void Object::load(std::string p, PandaFramework *f, WindowFramework *w){
    // node = Game::load_model(p);
    // node.reparent_to(Game::window->get_render());
    node = w->load_model(f->get_models(), p.c_str());
    node.reparent_to(w->get_render());
}

void Object::load_tex(std::string p){
    PT(Texture) myTexture = TexturePool::load_texture(p.c_str());
    PT(TextureStage) stage = TextureStage::get_default();
    node.set_texture(myTexture);
    node.set_tex_scale(stage, 3, 5);
}

void Object::set_scale(float x, float y, float z){
    node.set_scale(x, y, z);
}

void Object::set_scale(float s){
    node.set_scale(s, s, s);
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

