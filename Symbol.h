#include <map>

#if ! defined ( SYMBOL_H )
#define SYMBOL_H

using namespace std;

enum SYMBOL {VALUE, ADDITION, MULTIPLICATION, OPENINGPARENTHESIS, CLOSINGPARENTHESIS, END, EXPR};

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
    
    protected:

};
    


class Multiplication : public Symbol {
    public:
        Multiplication();
        virtual ~Multiplication();
        void print() override;
    
    protected:

};
    


class OpeningParenthesis : public Symbol {
    public:
        OpeningParenthesis();
        virtual ~OpeningParenthesis();
        void print() override;

    protected:

};
    
    

class ClosingParenthesis : public Symbol {
    public:
        ClosingParenthesis();
        virtual ~ClosingParenthesis();
        void print() override;
    
    protected:
    
};



class End : public Symbol {
    public:
        End();
        virtual ~End();
        void print() override;
        
    protected:

};



class Expr : public Symbol {
    public:
        Expr();
        virtual ~Expr();
        virtual double eval() = 0;
        virtual void print() override = 0;
    
    protected:

};



class Value : public Expr {
    public:
        Value(double v);
        ~Value();
        double eval() override;
        void print() override;
    
    protected:
        double number;

};



class ExprBin : public Expr {    
    public:
        ExprBin(Expr* leftValue, Expr* rightValue);
        virtual ~ExprBin();

    protected:
        Expr* leftExpr;
        Expr* rightExpr;

};



class PlusExpr : public ExprBin {
    public:
        PlusExpr(Expr* leftValue, Expr* rightValue);
        double eval() override;
        void print() override;
    
    protected:

};



class TimesExpr : public ExprBin {
    public:
        TimesExpr(Expr* leftValue, Expr* rightValue);
        double eval() override;
        void print() override;

    protected:

};





#endif // SYMBOL_H