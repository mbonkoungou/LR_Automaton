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
    // Uncomment the following lines to enable debug printing for shift operations:
    /*
    std::cout << "Shift: ";
    sy->print();
    std::cout << " | New state: " << st->getName() << std::endl;
    */
    lexer->MoveForward();
}

Symbol* Automaton::popSymbol() {
    if (!symbolStack.empty()) {
        Symbol* top = symbolStack.back();
        symbolStack.pop_back();
        return top;
    }
    std::cerr << "ERROR: Tried to pop from an empty symbol stack!" << std::endl;
    return nullptr;
}

void Automaton::popAndDestroySymbol() {
    if (!symbolStack.empty()) {
        Symbol* top = symbolStack.back();
        symbolStack.pop_back();
        delete top;
    } else {
        std::cerr << "ERROR: Tried to pop and delete from an empty symbol stack!" << std::endl;
    }
}

Symbol* Automaton::peekSymbol(size_t offset) const {
    if (offset < symbolStack.size())
        return symbolStack[symbolStack.size() - 1 - offset];
    std::cerr << "ERROR: Peek offset out of range!" << std::endl;
    return nullptr;
}

void Automaton::reduction(int n, Symbol *sy) {
    // Uncomment the following line to enable debug printing for reductions:
    /*
    std::cout << "Reduction: Combining " << n << " symbol(s) into: ";
    sy->print();
    std::cout << std::endl;
    */
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
    (void)sy; // Mark parameter as unused.
    stateStack.push_back(st);
    // Uncomment the following line to enable debug printing for goto transitions:
    // std::cout << "Goto Transition: Pushing new state: " << st->getName() << std::endl;
}

bool Automaton::isAccepting() const { return accepting; }

void Automaton::setAccepting(bool acc) { accepting = acc; }

void Automaton::Analysis() {
    bool analysis = false;
    Symbol* currentSymbol = lexer->GetSymbol();

    while (!analysis && currentSymbol) {
        // Uncomment the following block to show current state and symbol:
        /*
        State* currentState = stateStack.back();
        std::cout << "Current State: " << currentState->getName() << " | Processing symbol: ";
        currentSymbol->print();
        std::cout << std::endl;
        */
        State* currentState = stateStack.back();

        if (!currentState->transition(*this, currentSymbol)) {
            std::cerr << "ERROR: Invalid transition from state " << currentState->getName() << " with symbol ";
            currentSymbol->print();
            std::cerr << std::endl;
            return;
        }

        if (accepting) {
            analysis = true;
        }
        else {
            currentSymbol = lexer->GetSymbol();
            if (!currentSymbol) {
                std::cerr << "ERROR: Lexer returned nullptr!" << std::endl;
                return;
            }
        }
    }

    if (!symbolStack.empty()) {
        Symbol* finalSymbol = symbolStack.back();
        Expr* expression = dynamic_cast<Expr*>(finalSymbol);
        if (expression) {
            double result = expression->eval();
            std::cout << "Result = " << result << std::endl;
            // Print final syntax tree:
            std::cout << "\nFinal Syntax Tree:" << std::endl;
            expression->printTree();
        } else {
            std::cerr << "ERROR: Invalid final expression" << std::endl;
        }
    } else {
        std::cerr << "ERROR: No valid symbol found" << std::endl;
    }
}
