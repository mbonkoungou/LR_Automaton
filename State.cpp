#include <iostream>
using namespace std;

#include "State.h"
#include "Automaton.h"
#include "Symbol.h"

State::State(string name) : name(name) {}
State::~State() {}
void State::print() const {
    // (Debug print for state description has been commented out.)
    // cout << "Current State: " << name << endl;
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

bool State0::transition(Automaton &automaton, Symbol *s) {
    // Debug print commented out:
    // cout << "State0 handling symbol: ";
    // s->print();
    // cout << endl;
    switch (*s) {
    case VALUE:
        automaton.shift(s, new State3());
        return true;
    case OPENINGPARENTHESIS:
        automaton.shift(s, new State2());
        return true;
    case EXPR:
        automaton.gotoTransition(s, new State1());
        return true;
    default:
        cerr << "Syntax error in State0" << endl;
        return false;
    }
}

bool State1::transition(Automaton &automaton, Symbol *s) {
    // Debug print commented out:
    // cout << "State1 handling symbol: ";
    // s->print();
    // cout << endl;
    switch (*s) {
    case ADDITION:
        automaton.shift(s, new State4());
        return true;
    case MULTIPLICATION:
        automaton.shift(s, new State5());
        return true;
    case END:
        automaton.setAccepting(true);
        return true;
    default:
        cerr << "Syntax error in State1" << endl;
        return false;
    }
}

bool State2::transition(Automaton &automaton, Symbol *s) {
    // Debug print commented out:
    // cout << "State2 handling symbol: ";
    // s->print();
    // cout << endl;
    switch (*s) {
    case VALUE:
        automaton.shift(s, new State3());
        return true;
    case OPENINGPARENTHESIS:
        automaton.shift(s, new State2());
        return true;
    case EXPR:
        automaton.gotoTransition(s, new State6());
        return true;
    default:
        cerr << "Syntax error in State2" << endl;
        return false;
    }
}

bool State3::transition(Automaton &automaton, Symbol *s) {
    // Debug print commented out:
    // cout << "State3 handling symbol: ";
    // s->print();
    // cout << endl;
    switch (*s) {
    case ADDITION:
    case MULTIPLICATION:
    case CLOSINGPARENTHESIS:
    case END: {
         Value* valToken = dynamic_cast<Value*>(automaton.peekSymbol(0));
         if (!valToken) {
             cerr << "Reduction error: token is not a Value." << endl;
             return false;
         }
         NonTerminalValue* exprToken = new NonTerminalValue(valToken->eval());
         automaton.reduction(1, exprToken);
         return true;
    }
    default:
         cerr << "Syntax error in State3" << endl;
         return false;
    }
}

bool State4::transition(Automaton &automaton, Symbol *s) {
    // Debug print commented out:
    // cout << "State4 handling symbol: ";
    // s->print();
    // cout << endl;
    switch (*s) {
    case VALUE:
        automaton.shift(s, new State3());
        return true;
    case OPENINGPARENTHESIS:
        automaton.shift(s, new State2());
        return true;
    case EXPR:
        automaton.gotoTransition(s, new State7());
        return true;
    default:
        cerr << "Syntax error in State4" << endl;
        return false;
    }
}

bool State5::transition(Automaton &automaton, Symbol *s) {
    // Debug print commented out:
    // cout << "State5 handling symbol: ";
    // s->print();
    // cout << endl;
    switch (*s) {
    case VALUE:
        automaton.shift(s, new State3());
        return true;
    case OPENINGPARENTHESIS:
        automaton.shift(s, new State2());
        return true;
    case EXPR:
        automaton.gotoTransition(s, new State8());
        return true;
    default:
        cerr << "Syntax error in State5" << endl;
        return false;
    }
}

bool State6::transition(Automaton &automaton, Symbol *s) {
    // Debug print commented out:
    // cout << "State6 handling symbol: ";
    // s->print();
    // cout << endl;
    switch (*s) {
    case ADDITION:
        automaton.shift(s, new State4());
        return true;
    case MULTIPLICATION:
        automaton.shift(s, new State5());
        return true;
    case CLOSINGPARENTHESIS:
        automaton.shift(s, new State9());
        return true;
    default:
        cerr << "Syntax error in State6" << endl;
        return false;
    }
}

bool State7::transition(Automaton &automaton, Symbol *s) {
    // Debug print commented out:
    // cout << "State7 handling symbol: ";
    // s->print();
    // cout << endl;
    switch(*s) {
    case MULTIPLICATION:
        automaton.shift(s, new State5());
        return true;
    case ADDITION:
    case CLOSINGPARENTHESIS:
    case END: {
        Expr* rightExpr = dynamic_cast<Expr*>(automaton.peekSymbol(0));
        Expr* leftExpr  = dynamic_cast<Expr*>(automaton.peekSymbol(2));
        Expr* sumExpr = new PlusExpr(leftExpr, rightExpr);
        automaton.reduction(3, sumExpr);
        return true;
    }
    default:
        cerr << "Syntax error in State7" << endl;
        return false;
    }
}

bool State8::transition(Automaton &automaton, Symbol *s) {
    // Debug print commented out:
    // cout << "State8 handling symbol: ";
    // s->print();
    // cout << endl;
    switch (*s) {
    case ADDITION:
    case MULTIPLICATION:
    case CLOSINGPARENTHESIS:
    case END: {
        Expr* rightExpr = dynamic_cast<Expr*>(automaton.peekSymbol(0));
        Expr* leftExpr  = dynamic_cast<Expr*>(automaton.peekSymbol(2));
        Expr* productExpr = new TimesExpr(leftExpr, rightExpr);
        automaton.reduction(3, productExpr);
        return true;
    }
    default:
        cerr << "Syntax error in State8" << endl;
        return false;
    }
}

bool State9::transition(Automaton &automaton, Symbol *s) {
    // Debug print commented out:
    // cout << "State9 handling symbol: ";
    // s->print();
    // cout << endl;
    switch (*s) {
    case ADDITION:
    case MULTIPLICATION:
    case CLOSINGPARENTHESIS:
    case END: {
        Expr* e = dynamic_cast<Expr*>(automaton.peekSymbol(1));
        automaton.reduction(3, e);
        return true;
    }
    default:
        cerr << "Syntax error in State9" << endl;
        return false;
    }
}
