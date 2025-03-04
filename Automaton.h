#if ! defined ( AUTOMATON_H )
#define AUTOMATON_H

using namespace std;

#include "Symbol.h"
#include "Lexer.h"
#include "State.h"

class Automaton {

    public:
        Automaton();
        virtual ~Automaton();
        void shift(Symbol *sy, State *st);
        void simpleTransition(Symbol *sy, State *st);
        void reduction(int n, Symbol *sy);

    protected:
        vector<int>  symbolstack;
        vector<int>  statestack;
        
};

#endif // AUTOMATON_H