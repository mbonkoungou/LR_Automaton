#include <iostream>

#include "Symbol.h"

using namespace std;


Symbol::Symbol(int id) : ident(id) {}

Symbol::~Symbol() {}

void Symbol::print() {
    cout << "Symbol ID: " << ident << endl;
}



Addition::Addition() : Symbol(ADDITION) {}

Addition::~Addition() {}

void Addition::print() {
    cout << "Symbol: +" << endl;
}



Multiplication::Multiplication() : Symbol(MULTIPLICATION) {}

Multiplication::~Multiplication() {}

void Multiplication::print() {
    cout << "Symbol: *" << endl;
}



OpeningParenthesis::OpeningParenthesis() : Symbol(OPENINGPARENTHESIS) {}

OpeningParenthesis::~OpeningParenthesis() {}

void OpeningParenthesis::print() {
    cout << "Symbol: (" << endl;
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



Value::~Value() {}

Value::Value(double v) : number(v) {}

double Value::eval(const map<string, double>& values) {
    return number;
}

void Value::print() {
    cout << number;
}



ExprBin::ExprBin(Expr* l, Expr* r) : left(l), right(r) {}

ExprBin::~ExprBin() {
    delete left;
    delete right;
}



PlusExpr::PlusExpr(Expr* l, Expr* r) : ExprBin(l, r) {}

double PlusExpr::eval(const map<string, double>& vals) {
    return left->eval(vals) + right->eval(vals);
}

void PlusExpr::print() {
    cout << "("; left->print(); cout << " + "; right->print(); cout << ")";
}



TimesExpr::TimesExpr(Expr* l, Expr* r) : ExprBin(l, r) {}

double TimesExpr::eval(const map<string, double>& vals) {
    return left->eval(vals) * right->eval(vals);
}

void TimesExpr::print() {
    cout << "("; left->print(); cout << " * "; right->print(); cout << ")";
}
