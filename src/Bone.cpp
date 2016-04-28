//implementation of Bone class

#include "Bone.hpp"

void Bone::load(std::string p, PandaFramework *f, WindowFramework *w){
    node = w->load_model(f->get_models(), p.c_str());
    node.reparent_to(w->get_render());
    load_tex("models/tex/bone.png");
}
