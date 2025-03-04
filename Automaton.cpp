#include <iostream>

#include "Automaton.h"



Automaton::Automaton() {}



Automaton::~Automaton() {}



void Automaton::shift(Symbol *sy, State *st) {
    symbolstack.push_back(sy);
    statestack.push_back(st);
    lexer->Avancer();
}



void Automaton::simpleTransition(Symbol *sy, State *st) {
    symbolstack.push_back(sy);
    statestack.push_back(st);
}



void Automaton::reduction(int n, Symbol *sy) {
    for (int i=0; i<n; i++)
    {
        delete(statestack.back());
        statestack.pop_back();
    }
    statestack.back()->transition(*this, sy);
}
