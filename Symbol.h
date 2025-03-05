#include <map>

#if ! defined ( SYMBOL_H )
#define SYMBOL_H

using namespace std;

enum SYMBOL {VALUE, ADDITION, MULTIPLICATION, OPENINGPARENTHESIS, CLOSINGPARENTHESIS, END, EXPR};

class Symbol {

    public:
        Symbol(int id);
        virtual ~Symbol() {}
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
        virtual double eval(const map<string, double>& values) = 0;
        virtual void print() override = 0;
    
    protected:

};



class Value : public Expr {
    public:
        Value(double v);
        ~Value();
        double eval(const map<string, double>& values) override;
        void print() override;
    
    protected:
        double number;

};



class ExprBin : public Expr {    
    public:
        ExprBin(Expr* l, Expr* r);
        virtual ~ExprBin();

    protected:
        Expr* left;
        Expr* right;

};



class PlusExpr : public ExprBin {
    public:
        PlusExpr(Expr* l, Expr* r);
        double eval(const std::map<std::string, double>& values) override;
        void print() override;
    
    protected:

};



class TimesExpr : public ExprBin {
    public:
        TimesExpr(Expr* l, Expr* r);
        double eval(const std::map<std::string, double>& values) override;
        void print() override;

    protected:

};





#endif // SYMBOL_H