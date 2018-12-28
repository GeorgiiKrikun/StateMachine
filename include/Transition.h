#pragma once
#ifndef TRANSITION_H
#define TRANSITION_H
#include "state.h"

class Transition
{
    public:
        Transition(state& from, state& to, bool& flag);
        virtual ~Transition();

    protected:

    private:
        state* from;
        state* to;
        bool* transitionflag;

};

#endif // TRANSITION_H
