#include "../include/StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
    //dtor
}

void StateMachine::AddState(state& newstate){
    this->states.push_back(&newstate);
    this->NumberOfStates++;
    if (this->NumberOfStates == 1) {
        this->CurrentState = &newstate;
    }
}

int StateMachine::GetNumberOfStates(){
    return this->NumberOfStates;
}

void StateMachine::tick(){
    
}


