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

void state::addTransition(state* stateto, bool* transitionflag){
    this->TransitionTo.push_back(stateto);
    this->TransitionCondition.push_back(transitionflag);
    this->NumberOfTransitions++;
}

void state::PrintTransitionNames(){
    for (std::vector<state*>::iterator it = this->TransitionTo.begin(); it!=this->TransitionTo.end(); it++) {
        std::cout << (*it)->statename + '\n';
    }
}
