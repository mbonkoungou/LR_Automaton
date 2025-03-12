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

// ---------------------------------------------------------------------
// Expression Classes
// ---------------------------------------------------------------------
Expr::Expr() : Symbol(EXPR) {}
Expr::Expr(int id) : Symbol(id) {}
Expr::~Expr() {}

Value::Value(double v) : Expr(VALUE), number(v) {}
Value::~Value() {}
double Value::eval() {
    return number;
}
void Value::print() {
    cout << number;
}

// NEW: Tree printing for Value using plain ASCII characters
void Value::printTree(const std::string &prefix, bool isLeft) {
    cout << prefix << (isLeft ? "|--" : "`--") << number << endl;
}

ExprBin::ExprBin(Expr* leftValue, Expr* rightValue)
    : Expr(EXPR), leftExpr(leftValue), rightExpr(rightValue) {}

ExprBin::~ExprBin() {
    delete leftExpr;
    delete rightExpr;
}

PlusExpr::PlusExpr(Expr* leftValue, Expr* rightValue)
    : ExprBin(leftValue, rightValue) {}
double PlusExpr::eval() {
    return leftExpr->eval() + rightExpr->eval();
}
void PlusExpr::print() {
    cout << "(";
    leftExpr->print();
    cout << " + ";
    rightExpr->print();
    cout << ")";
}
// NEW: Tree printing for PlusExpr using plain ASCII
void PlusExpr::printTree(const std::string &prefix, bool isLeft) {
    cout << prefix << (isLeft ? "|--" : "`--") << "+" << endl;
    leftExpr->printTree(prefix + (isLeft ? "|   " : "    "), true);
    rightExpr->printTree(prefix + (isLeft ? "|   " : "    "), false);
}

TimesExpr::TimesExpr(Expr* leftValue, Expr* rightValue)
    : ExprBin(leftValue, rightValue) {}
double TimesExpr::eval() {
    return leftExpr->eval() * rightExpr->eval();
}
void TimesExpr::print() {
    cout << "(";
    leftExpr->print();
    cout << " * ";
    rightExpr->print();
    cout << ")";
}
// NEW: Tree printing for TimesExpr using plain ASCII
void TimesExpr::printTree(const std::string &prefix, bool isLeft) {
    cout << prefix << (isLeft ? "|--" : "`--") << "*" << endl;
    leftExpr->printTree(prefix + (isLeft ? "|   " : "    "), true);
    rightExpr->printTree(prefix + (isLeft ? "|   " : "    "), false);
}

NonTerminalValue::NonTerminalValue(double v) : Value(v) {
    this->ident = EXPR;
}
NonTerminalValue::~NonTerminalValue() {}
double NonTerminalValue::eval() {
    return Value::eval();
}
void NonTerminalValue::print() {
    Value::print();
}
// Inherit printTree from Value
