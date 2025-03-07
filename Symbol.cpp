#include <iostream>
#include "Symbol.h"

using namespace std;

Symbol::Symbol(int id) : ident(id) {}
Symbol::~Symbol() {}
void Symbol::print()
{
    cout << "Symbol ID: " << ident << endl;
}



Addition::Addition() : Symbol(ADDITION) {}
Addition::~Addition() {}
void Addition::print()
{
    cout << "Symbol: +" << endl;
}



Multiplication::Multiplication() : Symbol(MULTIPLICATION) {}
Multiplication::~Multiplication() {}
void Multiplication::print()
{
    cout << "Symbol: *" << endl;
}



OpeningParenthesis::OpeningParenthesis() : Symbol(OPENINGPARENTHESIS) {}
OpeningParenthesis::~OpeningParenthesis() {}
void OpeningParenthesis::print()
{
    cout << "Symbol: (" << endl;
}



ClosingParenthesis::ClosingParenthesis() : Symbol(CLOSINGPARENTHESIS) {}
ClosingParenthesis::~ClosingParenthesis() {}
void ClosingParenthesis::print()
{
    cout << "Symbol: )" << endl;
}



End::End() : Symbol(END) {}
End::~End() {}
void End::print()
{
    cout << "Symbol: END" << endl;
}



Expr::Expr() : Symbol(EXPR) {}
Expr::~Expr() {}
Expr::Expr(int id) : Symbol(id) {}



Value::Value(double v) : Expr(VALUE), number(v) {}
Value::~Value() {}
double Value::eval()
{
    return number;
}
void Value::print()
{
    cout << number;
}



ExprBin::ExprBin(Expr *leftValue, Expr *rightValue) : leftExpr(leftValue), rightExpr(rightValue) {}
ExprBin::~ExprBin()
{
    delete leftExpr;
    delete rightExpr;
}



PlusExpr::PlusExpr(Expr *leftValue, Expr *rightValue) : ExprBin(leftValue, rightValue) {}
double PlusExpr::eval()
{
    return leftExpr->eval() + rightExpr->eval();
}
void PlusExpr::print()
{
    cout << "(";
    leftExpr->print();
    cout << " + ";
    rightExpr->print();
    cout << ")";
}



TimesExpr::TimesExpr(Expr *leftValue, Expr *rightValue) : ExprBin(leftValue, rightValue) {}
double TimesExpr::eval()
{
    return leftExpr->eval() * rightExpr->eval();
}
void TimesExpr::print()
{
    cout << "(";
    leftExpr->print();
    cout << " * ";
    rightExpr->print();
    cout << ")";
}



NonTerminalValue::NonTerminalValue(double v) : Value(v) { this->ident = EXPR; } // On aurait pu assigner EXPR à ident dans le constructeur de Value
NonTerminalValue::~NonTerminalValue() {}
double NonTerminalValue::eval()
{
    return Value::eval();
}
void NonTerminalValue::print()
{
    Value::print();
}

