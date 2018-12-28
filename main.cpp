#include <iostream>
#include "include/state.h"
#include "include/StateMachine.h"


int main()
{
    std::cout << "Hello world!" << std::endl;
    StateMachine* Machine = new StateMachine(3);
    state* ready = new state();
    state* casting = new state();
    state* onCD = new state();
    ready->namestate("ready");
    casting->namestate("casting");
    onCD->namestate("onCD");
    std::cout << Machine->IsFunctional() << '\n';
    Machine->AddState(*ready);
    Machine->AddState(*casting);
    Machine->AddState(*onCD);
    std::cout << Machine->IsFunctional() << '\n';

    bool skillpressedflag = false;

    return 0;
}
