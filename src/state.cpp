#include "../include/state.h"

state::state()
{
}

state::~state()
{
    //dtor
}

void state::namestate(std::string name){
    this->statename = name;
}
