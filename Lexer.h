#if ! defined ( LEXER_H )
#define LEXER_H

using namespace std;

#include <vector>

class Symbol;


class Lexer {
    public:
        Lexer(string expression);
        virtual ~Lexer();
        void MoveForward();
        Symbol* GetSymbol();
        void ParseInputToSymbolList();

    protected:
        string inputStream;
        vector<Symbol*> symbolizedInputStack;
        size_t cursor;

};

#endif // LEXER_H