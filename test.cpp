#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

class state;

class Transition{
        public:
        Transition(bool & transitionCondition, short unsigned int priority, state & transitionTo ) {
            this->transitionCondition = &transitionCondition;
            this->priority = priority;
            this->transitionTo = &transitionTo;
        };    
        short unsigned int getPriority() const {
            return this->priority;
        }
        virtual bool shouldTransit() const {
            return *transitionCondition;
        }
        void printTransition() const;

        virtual state & initiateTransition(){
            *this->transitionCondition = false;
            return *this->transitionTo;
        }
        virtual void tick(float const & dt){
            return;
        }

        virtual void silentTick(float const & dt){
            return;
        }

        virtual void doWhenCurrentState(){
            return;
        }
        protected:
            bool* transitionCondition;

        private:
            
            short unsigned int priority = 0; //0 - highest priority
            state* transitionTo;
    };

class state
{
    public:
    

    
        state(char const * const s){
            this->name = s;
        };
        virtual ~state(){
            for (auto i : this->transitions){
                delete i;
            }
        };
        virtual state& tick(float const & dt) {
            for (auto it = this->transitions.begin(); it < this->transitions.end(); it++){
                (*it)->tick(dt);
                if ((*it)->shouldTransit()){
                    return (*it)->initiateTransition();
                }
            }
            return *this;    
        };

        
        virtual void silentTick(float const & dt){
            for (auto it = this->transitions.begin(); it < this->transitions.end(); it++){(*it)->silentTick(dt);}
            return;
        }

        virtual void doWhenCurrentState(){
            for (auto & i : transitions){
                i->doWhenCurrentState();
            }
            return;
        }

        void addTransition(bool& condition, state& transitionTo, short unsigned int priority){
            if (this->transitions.size() == 0) { this->transitions.push_back(new Transition(condition,priority,transitionTo)); }            
            else{
                auto it = this->transitions.begin();
                while(((*it)->getPriority() < priority) && (it < this->transitions.end()) ){
                    it++;
                }
                this->transitions.insert(it,new Transition(condition,priority,transitionTo));
            }
        };

        void addTransition(Transition * newTransition){
            if (!newTransition){return;}
            if (this->transitions.size() == 0) { this->transitions.push_back(newTransition); }
            else{
                auto it = this->transitions.begin();
                while(((*it)->getPriority() < newTransition->getPriority()) && (it < this->transitions.end()) ){
                    it++;
                }
                this->transitions.insert(it,newTransition);
            }            
        }
   
        std::string getName() const {
            return this->name;
        };

/*        void printState() const {
            std::cout << "STATE: " << this->getName() << std::endl;
            for (auto& i : transitions){
                i->printTransition();
            }
        };*/
    protected:

    private:

    std::string name;
    std::vector<Transition * > transitions;

};

void Transition::printTransition() const {
    std::cout << "TRANSITION TO: " << this->transitionTo->getName() << "; PRIORITY = " << priority << std::endl;
};

class TimedTransition : public Transition {
    public:
        TimedTransition(float transitionTime, short unsigned int priority, state & transitionTo ) : Transition(this->timeflag, priority, transitionTo)  {
            this->totaltimer = transitionTime;
        }
        virtual void tick(float const & dt) override {
            currenttimer+=dt;
            if (currenttimer > totaltimer) {
                currenttimer = totaltimer;
                this->timeflag=true;
            }
            return;
        }

        virtual void doWhenCurrentState() override {
            currenttimer = 0;
        }


    private:
        bool timeflag=false;
        float currenttimer=0;
        float totaltimer;
};

class AntiTransition : public Transition {
    public:
    AntiTransition(bool & transitionCondition, short unsigned int priority, state & transitionTo) : Transition(transitionCondition,priority,transitionTo){}
    virtual bool shouldTransit() const override {
        return !(Transition::shouldTransit());
    }
    virtual void doWhenCurrentState() override {
        *(this->transitionCondition) = true;
        return;
    }
};

class StateMachine {
    public:
        StateMachine(){};
        virtual ~StateMachine(){
            for (auto& i : states){
                delete i;
            }
        };
        void addState(state * stateToAdd){
            if (stateToAdd){
                this->states.push_back(stateToAdd);
            }
            if (states.size() == 1){
                currentstate = stateToAdd;
            }
            return;
        };
        void tick(float const & dt) {
            if (!currentstate) {
                throw "Ticking state machine before actually initializing";
            }
            for (auto it = this->states.begin(); it < this->states.end(); it++){
                if (*it == currentstate){
                    continue;
                } else {
                    (*it)->silentTick(dt);
                }
            }
            state * nextstate = & currentstate->tick(dt);
            if (nextstate != currentstate){
                nextstate->doWhenCurrentState();
            }
            currentstate = nextstate;
            return;
        };

        std::string getCurrentState() const{
            return this->currentstate->getName();

        }

        state * getStateByName(const char * stateName){
            for (const auto & i : states){
                if (i->getName() == stateName){
                    return i;
                }
            }
            return nullptr;
        }

        state & operator[](const char * stateName){ // gets state by name. Throws error if not found
            state * retrievedState = this->getStateByName(stateName);
            if (!retrievedState){
                throw "State does not exist";
            } 
            else {
                return *retrievedState;
            }
        }

    private:
        std::vector<state*> states;
        state* currentstate = nullptr;
};













int main(){
    std::cout <<std::string("State Machine test. Casting time = 0.5, CD = 1.0; 1 to imitate skill activation, d to activate skill disable, e to activate skill back") <<std::endl;
    StateMachine SM = StateMachine();
    //creating states
    SM.addState(new state("ready"));
    SM.addState(new state("casting"));
    SM.addState(new state("oncooldown"));
    SM.addState(new state("disabled"));
    bool skillButtonPressed = false, gotDisabled = false;
    SM["ready"].addTransition(new Transition(skillButtonPressed,1,SM["casting"]));
    SM["ready"].addTransition(new Transition(gotDisabled,0,SM["disabled"]));
    SM["casting"].addTransition(new TimedTransition(0.5f,1,SM["oncooldown"]));
    SM["casting"].addTransition(new Transition(gotDisabled,0,SM["disabled"]));
    SM["oncooldown"].addTransition(new TimedTransition(1.0f,1,SM["ready"]));
    SM["disabled"].addTransition(new AntiTransition(gotDisabled,0,SM["ready"]));

    std::string input;
    float t=0.0f;
    while (input != std::string("exit")){
        std::cin >> input;
        std::cout << "current time: " << t << " state: " << SM.getCurrentState(); 
        if (input == std::string("1")){
            skillButtonPressed = true;
        } else if (input == std::string("d")){
            gotDisabled = true;
        } else if (input == std::string("e")){
            gotDisabled = false;
        }
        SM.tick(0.1f);
        t+=0.1f;
        std::cout << " >> " << SM.getCurrentState() << std::endl;

    }

}

