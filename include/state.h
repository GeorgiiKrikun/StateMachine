#pragma once
#ifndef STATE_H
#define STATE_H
#include <string>
#include "Transition.h"

class Transition;
class state
{
    public:
        state();
        virtual ~state();
        void namestate(std::string name);
        int NumberOfTransitions;
    protected:

    private:
        std::string statename;
};

#endif // STATE_H
