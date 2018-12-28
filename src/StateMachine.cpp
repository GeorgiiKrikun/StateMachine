#include "../include/StateMachine.h"

StateMachine::StateMachine(int N)
{
    this->NumberOfStates = N;
    this->states = new state[N];
    this->CurrentNumberOfStates=0;
}

StateMachine::~StateMachine()
{
    //dtor
}

void StateMachine::AddState(state& newstate){
    if (this->CurrentNumberOfStates == this->NumberOfStates) { return; }
    this->states[this->CurrentNumberOfStates] = newstate;
    this->CurrentNumberOfStates++;
    if (this->CurrentNumberOfStates == this->NumberOfStates) {this->bIsFunctional = true;}
}

bool StateMachine::IsFunctional(){
    return this->bIsFunctional;
}

