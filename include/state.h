#pragma once
#ifndef STATE_H
#define STATE_H
#include <string>
#include <vector>
#include <iostream>

class state
{
    struct Transition{
        bool& TransitonCondition;
        short unsigned int Priority = 0;
        state& TransitionTo;
    };

    public:
        state();
        virtual ~state();

    protected:

    private:
    state& Tick(float const & dt) const;
    

    std::string name;
    std::vector<Transition> Transitions;

};



#endif // STATE_H
