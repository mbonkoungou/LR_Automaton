#include <map>

#if ! defined ( SYMBOL_H )
#define SYMBOL_H

using namespace std;



class Symbol {

    public:
        Symbol(int id) : ident(id) {}
        virtual ~Symbol() {}
        void print();
        operator int() const { return ident; }

    protected:
        int ident;

};



class Expr : public Symbol {
    
    public:
        Expr():Symbol(EXPR) {}
        virtual ~Expr() {}
        virtual double eval(const map<string, double> &valeurs) = 0;

    protected:

};



class SimpleSymbol : public Symbol {

};


#endif // SYMBOL_H