#include <iostream>

#include "Symbol.h"

using namespace std;


Symbol::Symbol(int id) : ident(id) {}

Symbol::~Symbol() {}

void Symbol::print() {
    std::cout << "Symbol ID: " << ident << std::endl;
}



ClosingParenthesis::ClosingParenthesis() : Symbol(CLOSINGPARENTHESIS) {}

ClosingParenthesis::~ClosingParenthesis() {}

void ClosingParenthesis::print() {
    cout << "Symbol: )" << endl;
}



End::End() : Symbol(END) {}

End::~End() {}

void End::print() {
    cout << "Symbol: END" << endl;
}



Expr::Expr() : Symbol(EXPR) {}

Expr::~Expr() {}



Value::Value(double v) : number(v) {}

double Value::eval(const std::map<std::string, double>& values) {
    return number;
}

void Value::display() {
    std::cout << number;
}


