#include <iostream>
#include <algorithm>
#include <string> 

#include "Automaton.h"



Automaton::Automaton(string inputStream) {
    this->lexer = new Lexer(inputStream);
    stateStack.push(new State0());
}



Automaton::~Automaton() {
    delete lexer;
    while (!stateStack.empty()) {
        delete stateStack.top();
        stateStack.pop();
    }
    while (!symbolStack.empty()) {
        delete symbolStack.top();
        symbolStack.pop();
    }
}



void Automaton::shift(Symbol *sy, State *st) {
    symbolStack.push(sy);
    stateStack.push(st);
    lexer->MoveForward();
}



void Automaton::simpleTransition(Symbol *sy, State *st) {
    symbolStack.push(sy);
    stateStack.push(st);
}



Symbol* Automaton::popSymbol() {
    if (!symbolStack.empty()) {
        Symbol* top = symbolStack.top();
        symbolStack.pop();
        return top;
    }
    cerr << "ERROR: Tried to pop from an empty symbol stack!" << endl;
    return nullptr;
}




void Automaton::popAndDestroySymbol() {
    if (!symbolStack.empty()) {
        Symbol* top = symbolStack.top();
        symbolStack.pop();
        delete top;
    } else {
        cerr << "ERROR: Tried to pop and delete from an empty symbol stack!" << endl;
    }
}




void Automaton::reduction(int n, Symbol *sy) {
    for (int i = 0; i < n; i++) {
        if (!stateStack.empty()) {
            delete stateStack.top();
            stateStack.pop();
        }
        if (!symbolStack.empty()) {
            delete symbolStack.top();
            symbolStack.pop();
        }
    }

    if (!stateStack.empty()) {
        stateStack.top()->transition(*this, sy);
        symbolStack.push(sy);
    }
}



void Automaton::Analysis() {
    bool analysis = false;
    Symbol* currentSymbol = lexer->GetSymbol();

    while (!analysis && currentSymbol) {
        State* currentState = stateStack.top();

        if (!currentState->transition(*this, currentSymbol)) {
            cerr << "ERROR: Invalid transition from state " << stateStack.top()->getName() << " with symbol " << *currentSymbol << endl;
            return;
        }

        if ((int)(*lexer->GetSymbol()) == END && stateStack.size() == 1) {
            analysis = true;
        } else {
            currentSymbol = lexer->GetSymbol();
            if (!currentSymbol) {
                cerr << "ERROR: Lexer returned nullptr!" << endl;
                return;
            }
        }
    }

    if (!symbolStack.empty()) {
        Symbol* finalSymbol = symbolStack.top();
        Expr* expression = dynamic_cast<Expr*>(finalSymbol);
        if (expression) {
            double result = expression->eval();
            cout << "Result = " << result << endl;
        } else {
            cerr << "ERROR: Invalid final expression" << endl;
        }
    } else {
        cerr << "ERROR: No valid symbol found" << endl;
    }
}


