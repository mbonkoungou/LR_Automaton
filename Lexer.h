#if ! defined ( LEXER_H )
#define LEXER_H

using namespace std;

#include <vector>


class Lexer {

    public:
        Lexer(string expression);
        virtual ~Lexer();
        void MoveForward();
        Symbol* GetSymbol();
        void ParseInputToSymbolStack();

    protected:
        string inputStream;
        vector<Symbol*> symbolizedInputStack;
        size_t cursor;
        void ParseInputToSymbolList();

};

#endif // LEXER_H