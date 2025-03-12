#ifndef SYMBOL_H
#define SYMBOL_H

#include <map>
#include <string>

// The IDs used for our symbols.
enum SYMBOL {
    VALUE,
    ADDITION,
    MULTIPLICATION,
    OPENINGPARENTHESIS,
    CLOSINGPARENTHESIS,
    END,
    EXPR
};

class Symbol {
public:
    Symbol(int id);
    virtual ~Symbol();
    virtual void print();
    operator int() const { return ident; }

protected:
    int ident;
};

class Addition : public Symbol {
public:
    Addition();
    virtual ~Addition();
    void print() override;
};

class Multiplication : public Symbol {
public:
    Multiplication();
    virtual ~Multiplication();
    void print() override;
};

class OpeningParenthesis : public Symbol {
public:
    OpeningParenthesis();
    virtual ~OpeningParenthesis();
    void print() override;
};

class ClosingParenthesis : public Symbol {
public:
    ClosingParenthesis();
    virtual ~ClosingParenthesis();
    void print() override;
};

class End : public Symbol {
public:
    End();
    virtual ~End();
    void print() override;
};

// ---------------------------------------------------------------------
// Expression classes
// ---------------------------------------------------------------------

class Expr : public Symbol {
public:
    Expr();
    Expr(int id);
    virtual ~Expr();

    virtual double eval() = 0;
    virtual void print() override = 0;

    // NEW: Prints the expression as a tree with branches
    virtual void printTree(const std::string &prefix = "", bool isLeft = true) = 0;
};

class Value : public Expr {
public:
    Value(double v);
    ~Value();
    double eval() override;
    void print() override;

    // NEW: Tree printing
    void printTree(const std::string &prefix = "", bool isLeft = true) override;

protected:
    double number;
};

class ExprBin : public Expr {
public:
    ExprBin(Expr* leftValue, Expr* rightValue);
    virtual ~ExprBin();

    Expr* leftExpr;
    Expr* rightExpr;

    // We'll implement printTree() in the derived classes (PlusExpr, TimesExpr)
};

class PlusExpr : public ExprBin {
public:
    PlusExpr(Expr* leftValue, Expr* rightValue);
    double eval() override;
    void print() override;

    // NEW: Tree printing
    void printTree(const std::string &prefix = "", bool isLeft = true) override;
};

class TimesExpr : public ExprBin {
public:
    TimesExpr(Expr* leftValue, Expr* rightValue);
    double eval() override;
    void print() override;

    // NEW: Tree printing
    void printTree(const std::string &prefix = "", bool isLeft = true) override;
};

// Used for intermediate reductions
class NonTerminalValue : public Value {
public:
    NonTerminalValue(double v);
    ~NonTerminalValue();
    double eval() override;
    void print() override;

    // We can reuse Value's printTree or override if needed
    void printTree(const std::string &prefix = "", bool isLeft = true) override {
        // Same as Value
        Value::printTree(prefix, isLeft);
    }
};

#endif // SYMBOL_H
