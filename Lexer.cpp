#include <iostream>
#include <cctype>
#include <string>
#include <cstdlib>
#include <stdexcept>


using namespace std;

#include "Lexer.h"
#include "Symbol.h"



Lexer::Lexer(string expression) : inputStream(expression), cursor(0) {
    ParseInputToSymbolList();
}



Lexer::~Lexer() {
    for (size_t i = 0; i < symbolizedInputStack.size(); i++) {
        delete symbolizedInputStack[i];
    }
}



Symbol* Lexer::GetSymbol() {
    if (cursor < symbolizedInputStack.size()) {
        return symbolizedInputStack[cursor];
    }
    return nullptr;
}



void Lexer::MoveForward() {
    if (cursor < symbolizedInputStack.size()) {
        cursor++;
    }
}



void Lexer::ParseInputToSymbolList() {
    size_t i = 0;
    while (i < inputStream.size()) {
        char c = inputStream[i];
        if (isspace(c)) {
            i++;
            continue;
        }

        if (c == '+') {
            symbolizedInputStack.push_back(new Addition());
            i++;
        }
        else if (c == '*') {
            symbolizedInputStack.push_back(new Multiplication());
            i++;
        }
        else if (c == '(') {
            symbolizedInputStack.push_back(new OpeningParenthesis());
            i++;
        }
        else if (c == ')') {
            symbolizedInputStack.push_back(new ClosingParenthesis());
            i++;
        }

        else if (isdigit(c)) {
            size_t length = 0;
            while ((i + length) < inputStream.size() &&
                   (isdigit(inputStream[i + length]) || inputStream[i + length] == '.')) {
                length++;
            }
            double value = stod(inputStream.substr(i, length));
            symbolizedInputStack.push_back(new Value(value));
            i += length;
        }
        else {
            string msg = "Unexpected character: ";
            msg.push_back(c);
            throw runtime_error(msg);
        }
    }

    symbolizedInputStack.push_back(new End());
}


