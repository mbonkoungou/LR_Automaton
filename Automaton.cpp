#include <iostream>
#include <algorithm>

#include "Automaton.h"




Automaton::Automaton(string inputStream) {
    this->lexer = new Lexer(inputStream);
    State0 *start = new State0();
    statestack.push(start);
}



Automaton::~Automaton() {
    delete lexer;

    while (!statestack.empty()) {
        delete statestack.top();
        statestack.pop();
    }
}



void Automaton::shift(Symbol *sy, State *st) {
    symbolstack.push(sy);
    statestack.push(st);
    lexer->Avancer();
}



void Automaton::simpleTransition(Symbol *sy, State *st) {
    symbolstack.push(sy);
    statestack.push(st);
}




void Automaton::reduction(int n, Symbol *sy) {
    for (int i = 0; i < n; i++) {
        if (!statestack.empty()) {
            delete statestack.top();
            statestack.pop();
        }
    }

    if (!statestack.empty()) {
        statestack.top()->transition(*this, sy);
    }
}



void Automaton::analysis()
{

}
