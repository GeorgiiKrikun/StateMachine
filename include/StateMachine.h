#pragma once
#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "state.h"
#include <vector>
class StateMachine
{
    public:
        StateMachine(int N);
        virtual ~StateMachine();
        void AddState(state& newstate);
        bool IsFunctional();
    protected:

    private:
        state* states;
        int NumberOfStates;
        int CurrentNumberOfStates;
        bool bIsFunctional = false;
};

#endif // STATEMACHINE_H
