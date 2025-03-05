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
        virtual void display() = 0;
};



class Value : public Expr {
    private:
        double number;
    public:
        Value(double v);
        ~Value() {}
        double eval(const map<string, double>& values) override;
        void display() override;
};





#endif // SYMBOL_H