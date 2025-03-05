#include <iostream>

using namespace std;

#include "State.h"



State::State(string name) : name(name) {}



State::~State() {}



void State::print() const {
    cout << "Current State: " << name << endl;
}



State0::State0() : State("State0") {}
State1::State1() : State("State1") {}
State2::State2() : State("State2") {}
State3::State3() : State("State3") {}
State4::State4() : State("State4") {}
State5::State5() : State("State5") {}
State6::State6() : State("State6") {}
State7::State7() : State("State7") {}
State8::State8() : State("State8") {}
State9::State9() : State("State9") {}



bool State0::transition(Automaton &Automaton, Symbol *s) {
    switch (*s)
    {
    case VALUE:
        Automaton.shift(s, new State3());
        break;
    case OPENINGPARENTHESIS:
        Automaton.shift(s, new State2());
        break;   
    case EXPR:
        Automaton.simpleTransition(s, new State1());
        break; 
    default:
        cout<<"Syntax error"<<endl;
        return false;
    }
    return true;

}



bool State1::transition(Automaton &Automaton, Symbol *s) {
    switch (*s)
    {
    case ADDITION:
        Automaton.shift(s, new State4());
        break;
    case MULTIPLICATION:
        Automaton.shift(s, new State5());
        break;
    case END:
        break;    
    default:
        cout<<"Syntax error"<<endl;
        return false;
    }
    return true;

}



bool State2::transition(Automaton &Automaton, Symbol *s) {
    switch (*s)
    {
    case VALUE:
        Automaton.shift(s, new State3());
        break;
    case OPENINGPARENTHESIS:
        Automaton.shift(s, new State2());
        break;
    case EXPR:
        Automaton.simpleTransition(s, new State6());
        break;    
    default:
        cout<<"Syntax error"<<endl;
        return false;
    }
    return true;

}



bool State3::transition(Automaton &Automaton, Symbol *s) {
    switch (*s)
    {
    case ADDITION:
        Automaton.reduction(1, new Addition());
        break;
    case MULTIPLICATION:
        Automaton.reduction(1, new Multiplication());
        break;
    case CLOSINGPARENTHESIS:
        Automaton.reduction(1, new ClosingParenthesis());
        break;
    case END:
        Automaton.reduction(1, new End());
        break;    
    default:
        cout<<"Syntax error"<<endl;
        return false;
    }
    return true;

}



bool State4::transition(Automaton &Automaton, Symbol *s) {
    switch (*s)
    {
    case VALUE:
        Automaton.shift(s, new State3());
        break;
    case OPENINGPARENTHESIS:
        Automaton.shift(s, new State2());
        break;
    case EXPR:
        Automaton.simpleTransition(s, new State7());
        break;    
    default:
        cout<<"Syntax error"<<endl;
        return false;
    }
    return true;

}



bool State5::transition(Automaton &Automaton, Symbol *s) {
    switch (*s)
    {
    case VALUE:
        Automaton.shift(s, new State3());
        break;
    case OPENINGPARENTHESIS:
        Automaton.shift(s, new State2());
        break;
    case EXPR:
        Automaton.simpleTransition(s, new State8());
        break;    
    default:
        cout<<"Syntax error"<<endl;
        return false;
    }
    return true;

}



bool State6::transition(Automaton &Automaton, Symbol *s) {
    switch (*s)
    {
    case ADDITION:
        Automaton.shift(s, new State4());
        break;
    case MULTIPLICATION:
        Automaton.shift(s, new State5());
        break;
    case CLOSINGPARENTHESIS:
        Automaton.shift(s, new State9());
        break;    
    default:
        cout<<"Syntax error"<<endl;
        return false;
    }
    return true;

}



bool State7::transition(Automaton &Automaton, Symbol *s) {
    switch (*s)
    {
    case ADDITION:
        Automaton.reduction(3, new Addition());
        break;
    case MULTIPLICATION:
        Automaton.shift(s, new State5());
        break;
    case CLOSINGPARENTHESIS:
        Automaton.reduction(3, new ClosingParenthesis());
        break;
    case END:
        Automaton.reduction(3, new End());
        break;
    default:
        cout<<"Syntax error"<<endl;
        return false;
    }
    return true;

}



bool State8::transition(Automaton &Automaton, Symbol *s) {
    switch (*s)
    {
    case ADDITION:
        Automaton.reduction(3, new Addition());
        break;
    case MULTIPLICATION:
        Automaton.reduction(3, new Multiplication());
        break;
    case CLOSINGPARENTHESIS:
        Automaton.reduction(3, new ClosingParenthesis());
        break;
    case END:
        Automaton.reduction(3, new End());
        break;
    default:
        cout<<"Syntax error"<<endl;
        return false;
    }
    return true;

}



bool State9::transition(Automaton &Automaton, Symbol *s) {
    switch (*s)
    {
    case ADDITION:
        Automaton.reduction(3, new Addition());
        break;
    case MULTIPLICATION:
        Automaton.reduction(3, new Multiplication());
        break;
    case CLOSINGPARENTHESIS:
        Automaton.reduction(3, new ClosingParenthesis());
        break;
    case END:
        Automaton.reduction(3, new End());
        break;
    default:
        cout<<"Syntax error"<<endl;
        return false;
    }
    return true;

}
