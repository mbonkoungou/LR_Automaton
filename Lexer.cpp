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
    int parenCount = 0; // tracks the net number of '(' minus ')'
    int tokenCount = 0; // counts tokens as they are produced

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
            // Implicit multiplication: if the previous token was a number or a ')'
            if (!symbolizedInputStack.empty()) {
                Symbol* lastToken = symbolizedInputStack.back();
                int tokenType = *lastToken;
                if (tokenType == VALUE || tokenType == CLOSINGPARENTHESIS) {
                    cout << "Notice: Implicit multiplication detected. Inserting '*' before '('\n";
                    symbolizedInputStack.push_back(new Multiplication());
                    tokenCount++;
                }
            }
            symbolizedInputStack.push_back(new OpeningParenthesis());
            tokenCount++;
            parenCount++;
            i++;
            continue;
        }
        else if (c == ')') {
            // Check for empty parentheses: if the last token is an opening parenthesis.
            if (!symbolizedInputStack.empty() && ((int)*symbolizedInputStack.back() == OPENINGPARENTHESIS)) {
                throw runtime_error("Syntax error: Empty parentheses '()' are not allowed at token #" 
                                      + to_string(tokenCount + 1) + ". An expression is expected between '(' and ')'.");
            }
            parenCount--;
            if (parenCount < 0) {
                throw runtime_error("Syntax error: Unmatched closing parenthesis detected at token #"
                                      + to_string(tokenCount + 1) + ". No corresponding opening parenthesis found.");
            }
            symbolizedInputStack.push_back(new ClosingParenthesis());
            tokenCount++;
            i++;
            continue;
        }
        // ---------------------------------------------------------
        // Operators '+' and '*'
        // ---------------------------------------------------------
        else if (c == '+') {
            size_t j = i + 1;
            while (j < inputStream.size() && isspace(inputStream[j])) j++;
            if (j >= inputStream.size() || (!isdigit(inputStream[j]) && inputStream[j] != '(')) {
                throw runtime_error("Syntax error: '+' operator at token #" + to_string(tokenCount + 1)
                                      + " is missing an operand. A numeric value or subexpression is expected after '+'.");
            }
            symbolizedInputStack.push_back(new Addition());
            tokenCount++;
            i++;
            continue;
        }
        else if (c == '*') {
            size_t j = i + 1;
            while (j < inputStream.size() && isspace(inputStream[j])) j++;
            if (j >= inputStream.size() || (!isdigit(inputStream[j]) && inputStream[j] != '(')) {
                throw runtime_error("Syntax error: '*' operator at token #" + to_string(tokenCount + 1)
                                      + " is missing an operand. A numeric value or subexpression is expected after '*'.");
            }
            symbolizedInputStack.push_back(new Multiplication());
            tokenCount++;
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
            tokenCount++;
            i += length;
            continue;
        }
        // ---------------------------------------------------------
        // Unexpected character
        // ---------------------------------------------------------
        else {
            throw runtime_error("Syntax error: Unexpected character '" + string(1, c)
                                  + "' encountered at token #" + to_string(tokenCount + 1)
                                  + ". Only digits, '+', '*', and parentheses are allowed.");
        }
    }

    if (parenCount > 0) {
        throw runtime_error("Syntax error: " + to_string(parenCount)
                              + " unmatched opening parenthesis" + (parenCount > 1 ? "es" : "")
                              + " detected. Each '(' must be closed by a matching ')'.");
    }

    // Push the end-of-input symbol.
    symbolizedInputStack.push_back(new End());
    tokenCount++;
}
