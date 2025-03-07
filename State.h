#ifndef STATE_H
#define STATE_H

using namespace std;

#include "Symbol.h"

class Automaton;



class State {
    public:
        State(string name);
        virtual ~State();
        void print() const;
        virtual bool transition(Automaton &automaton, Symbol *s) = 0;
        string getName() const { return name; }

    protected:
        string name;

};



class State0 : public State {
    public:
        State0();
        bool transition(Automaton &Automaton, Symbol *s) override;
    
    protected:

};

class State1 : public State {
    public:
        State1();
        bool transition(Automaton &Automaton, Symbol *s) override;

    protected:

};

class State2 : public State {
    public:
        State2();
        bool transition(Automaton &Automaton, Symbol *s) override;

    protected:

};

class State3 : public State {
    public:
        State3();
        bool transition(Automaton &Automaton, Symbol *s) override;

    protected:

};

class State4 : public State {
    public:
        State4();
        bool transition(Automaton &Automaton, Symbol *s) override;

    protected:

};

class State5 : public State {
    public:
        State5();
        bool transition(Automaton &Automaton, Symbol *s) override;

    protected:

};

class State6 : public State {
    public:
        State6();
        bool transition(Automaton &Automaton, Symbol *s) override;

    protected:

};

class State7 : public State {
    public:
        State7();
        bool transition(Automaton &Automaton, Symbol *s) override;

    protected:

};

class State8 : public State {
    public:
        State8();
        bool transition(Automaton &Automaton, Symbol *s) override;

    protected:

};

class State9 : public State {
    public:
        State9();
        bool transition(Automaton &Automaton, Symbol *s) override;

    protected:

};

#endif // STATE_H
