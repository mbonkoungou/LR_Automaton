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
        void reduction(int n, Symbol *sy);
        void analysis();

    protected:
        stack<Symbol *> symbolstack;
        stack<State *> statestack;
        Lexer *lexer;

};

#endif // AUTOMATON_H