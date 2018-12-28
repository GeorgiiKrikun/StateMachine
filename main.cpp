#include <iostream>
#include "include/state.h"
#include "include/StateMachine.h"

int main()
{
    std::cout << "Hello world!" << std::endl;
    bool skillpressedflag = false;

    StateMachine* Machine = new StateMachine();
    state* ready = new state();
    state* casting = new state();
    state* onCD = new state();
    ready->namestate("ready");
    casting->namestate("casting");
    onCD->namestate("onCD");
    ready->addTransition(casting, &skillpressedflag);

    Machine->AddState(*ready);
    Machine->AddState(*casting);
    Machine->AddState(*onCD);
    Machine->CurrentState->PrintTransitionNames();
    std::cout << Machine->GetNumberOfStates() << '\n';
    return 0;
}
