#include <iostream>
#include <algorithm>
#include <string> 

#include "Automaton.h"
#include "State.h"
#include "Lexer.h"

Automaton::Automaton(string inputStream) {
    this->lexer = new Lexer(inputStream);
    stateStack.push_back(new State0());
}

Automaton::~Automaton() {
    delete lexer;
    while (!stateStack.empty()) {
        delete stateStack.back();
        stateStack.pop_back();
    }
    while (!symbolStack.empty()) {
        delete symbolStack.back();
        symbolStack.pop_back();
    }
}

void Automaton::shift(Symbol *sy, State *st) {
    symbolStack.push_back(sy);
    stateStack.push_back(st);
    // Log the shift operation
    cout << "Shift: ";
    sy->print();
    cout << " | New state: " << st->getName() << endl;
    lexer->MoveForward();
}

Symbol* Automaton::popSymbol() {
    if (!symbolStack.empty()) {
        Symbol* top = symbolStack.back();
        symbolStack.pop_back();
        return top;
    }
    cerr << "ERROR: Tried to pop from an empty symbol stack!" << endl;
    return nullptr;
}

void Automaton::popAndDestroySymbol() {
    if (!symbolStack.empty()) {
        Symbol* top = symbolStack.back();
        symbolStack.pop_back();
        delete top;
    } else {
        cerr << "ERROR: Tried to pop and delete from an empty symbol stack!" << endl;
    }
}

Symbol* Automaton::peekSymbol(size_t offset) const {
    if (offset < symbolStack.size())
        return symbolStack[symbolStack.size() - 1 - offset];
    cerr << "ERROR: Peek offset out of range!" << endl;
    return nullptr;
}

void Automaton::reduction(int n, Symbol *sy) {
    cout << "Reduction: Combining " << n << " symbol(s) into: ";
    sy->print();
    cout << endl;
    for (int i = 0; i < n; i++) {
        if (!stateStack.empty()) {
            delete stateStack.back();
            stateStack.pop_back();
        }
        if (!symbolStack.empty()) {
            symbolStack.pop_back();
        }
    }
    symbolStack.push_back(sy);
    
    if (!stateStack.empty()) {
        stateStack.back()->transition(*this, sy);
    }
}

void Automaton::gotoTransition(Symbol *sy, State *st) {
    stateStack.push_back(st);
    cout << "Goto Transition: Pushing new state: " << st->getName() << endl;
}

bool Automaton::isAccepting() const { return accepting; }

void Automaton::setAccepting(bool acc) { accepting = acc; }

void Automaton::Analysis() {
    bool analysis = false;
    Symbol* currentSymbol = lexer->GetSymbol();

    while (!analysis && currentSymbol) {
        State* currentState = stateStack.back();
        cout << "Current State: " << currentState->getName() << " | Processing symbol: ";
        currentSymbol->print();
        cout << endl;

        if (!currentState->transition(*this, currentSymbol)) {
            cerr << "ERROR: Invalid transition from state " << currentState->getName() << " with symbol ";
            currentSymbol->print();
            cerr << endl;
            return;
        }

        if (accepting) {
            analysis = true;
        }
        else {
            currentSymbol = lexer->GetSymbol();
            if (!currentSymbol) {
                cerr << "ERROR: Lexer returned nullptr!" << endl;
                return;
            }
        }
    }

    if (!symbolStack.empty()) {
        Symbol* finalSymbol = symbolStack.back();
        Expr* expression = dynamic_cast<Expr*>(finalSymbol);
        if (expression) {
            double result = expression->eval();
            cout << "Result = " << result << endl;
            cout << "Final Syntax Tree: ";
            expression->print();
            cout << endl;
        } else {
            cerr << "ERROR: Invalid final expression" << endl;
        }
    } else {
        cerr << "ERROR: No valid symbol found" << endl;
    }
}
