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
    int parenCount = 0; // track number of '(' minus ')'

    while (i < inputStream.size()) {
        char c = inputStream[i];
        if (isspace(c)) {
            i++;
            continue;
        }

        // ---------------------------------------------------------
        // Parentheses and implicit multiplication
        // ---------------------------------------------------------
        if (c == '(') {
            // Implicit multiplication: if previous token was a number or a ')'
            if (!symbolizedInputStack.empty()) {
                Symbol* lastToken = symbolizedInputStack.back();
                int tokenType = *lastToken;
                if (tokenType == VALUE || tokenType == CLOSINGPARENTHESIS) {
                    cout << "Notice: Implicit multiplication detected. Inserting '*' before '('\n";
                    symbolizedInputStack.push_back(new Multiplication());
                }
            }
            symbolizedInputStack.push_back(new OpeningParenthesis());
            parenCount++;
            i++;
            continue;
        }
        else if (c == ')') {
            parenCount--;
            if (parenCount < 0) {
                // More closing than opening at this point.
                throw runtime_error("Syntax error: too many closing parentheses at position " + to_string(i));
            }
            symbolizedInputStack.push_back(new ClosingParenthesis());
            i++;
            continue;
        }
        // ---------------------------------------------------------
        // Operators + and *
        // ---------------------------------------------------------
        else if (c == '+') {
            size_t j = i + 1;
            while (j < inputStream.size() && isspace(inputStream[j])) j++;
            if (j >= inputStream.size() || (!isdigit(inputStream[j]) && inputStream[j] != '(')) {
                throw runtime_error("Error: '+' operator missing an operand at position " + to_string(i));
            }
            symbolizedInputStack.push_back(new Addition());
            i++;
            continue;
        }
        else if (c == '*') {
            size_t j = i + 1;
            while (j < inputStream.size() && isspace(inputStream[j])) j++;
            if (j >= inputStream.size() || (!isdigit(inputStream[j]) && inputStream[j] != '(')) {
                throw runtime_error("Error: '*' operator missing an operand at position " + to_string(i));
            }
            symbolizedInputStack.push_back(new Multiplication());
            i++;
            continue;
        }
        // ---------------------------------------------------------
        // Numeric values
        // ---------------------------------------------------------
        else if (isdigit(c)) {
            size_t length = 0;
            while ((i + length) < inputStream.size() &&
                   (isdigit(inputStream[i + length]) || inputStream[i + length] == '.')) {
                length++;
            }
            double value = stod(inputStream.substr(i, length));
            symbolizedInputStack.push_back(new Value(value));
            i += length;
            continue;
        }
        // ---------------------------------------------------------
        // Unexpected character
        // ---------------------------------------------------------
        else {
            throw runtime_error(string("Unexpected character '") + c + "' at position " + to_string(i));
        }
    }

    if (parenCount > 0) {
        throw runtime_error("Syntax error: missing " + to_string(parenCount) + " closing parenthesis" + (parenCount > 1 ? "es" : ""));
    }

    // Push the end-of-input symbol.
    symbolizedInputStack.push_back(new End());
}
