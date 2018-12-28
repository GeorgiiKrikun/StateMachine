#pragma once
#ifndef STATE_H
#define STATE_H
#include <string>
#include <vector>
#include <iostream>

class state
{
    public:
        state();
        virtual ~state();
        void namestate(std::string name);
        void addTransition(state* stateto, bool* transitionflag);
        void PrintTransitionNames();
    protected:

    private:
        std::string statename;
        std::vector<state*> TransitionTo;
        std::vector<bool*> TransitionCondition;
        int NumberOfTransitions;
};

#endif // STATE_H
