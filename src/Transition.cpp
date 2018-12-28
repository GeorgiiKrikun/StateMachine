#include "Transition.h"

Transition::Transition(state& from, state& to, bool& flag)
{
    this->from = &from;
    this->to = &to;
    this->transitionflag = &flag;
}


Transition::~Transition()
{
    //dtor
}
