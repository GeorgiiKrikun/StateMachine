#pragma once
#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "state.h"
#include <vector>
class StateMachine
{
    public:
        StateMachine();
        virtual ~StateMachine();
        void AddState(state& newstate);
        int GetNumberOfStates();
        void tick();
        state* CurrentState;

    protected:

    private:
        std::vector<state*> states;
        int NumberOfStates=0;
};

#endif // STATEMACHINE_H
