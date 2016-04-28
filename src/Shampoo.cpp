//implementation of Shampoo class

#include "Shampoo.hpp"

void Shampoo::load(std::string p, PandaFramework *f, WindowFramework *w){
    node = w->load_model(f->get_models(), p.c_str());
    node.reparent_to(w->get_render());
    load_tex("models/tex/shampoo2.png");
}
