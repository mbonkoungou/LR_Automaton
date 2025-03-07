#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <vector>
#include <string>
#include "Symbol.h"
#include "Lexer.h"
#include "State.h"

using namespace std;

class Automaton {
    public:
        Automaton(string inputStream);
        virtual ~Automaton();

        void shift(Symbol *sy, State *st);
        Symbol* popSymbol();
        void popAndDestroySymbol();
        void reduction(int n, Symbol *sy);
        void Analysis();
        Symbol* peekSymbol(size_t offset = 0) const;
        bool isAccepting() const;
        void setAccepting(bool acc);
        void gotoTransition(Symbol *sy, State *st);

    protected:
        vector<Symbol*> symbolStack;
        vector<State*> stateStack;
        Lexer *lexer;
        bool accepting = false;

};

#endif // AUTOMATON_H
