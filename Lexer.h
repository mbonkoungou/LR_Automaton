#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <memory>

using namespace std;

class Symbol;

class Lexer {
public:
    Lexer(string expression);
    virtual ~Lexer() = default; // unique_ptr handles deletion
    void MoveForward();
    Symbol* GetSymbol();
    void ParseInputToSymbolList();

protected:
    string inputStream;
    // Now using unique_ptr to manage tokens automatically.
    vector<unique_ptr<Symbol>> symbolizedInputStack;
    size_t cursor;
};

#endif // LEXER_H
