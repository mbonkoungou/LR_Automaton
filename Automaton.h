#if ! defined ( AUTOMATON_H )
#define AUTOMATON_H

using namespace std;

#include <stack>
#include "Symbol.h"
#include "Lexer.h"
#include "State.h"



class Automaton {

    public:
        Automaton(string inputStream);
        virtual ~Automaton();
        void shift(Symbol *sy, State *st);
        void simpleTransition(Symbol *sy, State *st);
        Symbol* popSymbol();
        void popAndDestroySymbol();
        void reduction(int n, Symbol *sy);
        void Analysis();

    protected:
        stack<Symbol*> symbolStack;
        stack<State*>  stateStack;
        Lexer *lexer;

};

#endif // AUTOMATON_H