#include <iostream>
#include <cctype>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <memory>  // needed for unique_ptr and make_unique

using namespace std;

#include "Lexer.h"
#include "Symbol.h"

// If compiling with C++11, include this compatibility snippet for make_unique:
#if __cplusplus <= 201103L
namespace std {
    template<typename T, typename... Args>
    unique_ptr<T> make_unique(Args&&... args) {
         return unique_ptr<T>(new T(forward<Args>(args)...));
    }
}
#endif

Lexer::Lexer(string expression) : inputStream(expression), cursor(0) {
    ParseInputToSymbolList();
}

// Destructor is defaulted in the header; unique_ptr frees tokens automatically.

Symbol* Lexer::GetSymbol() {
    if (cursor < symbolizedInputStack.size()) {
        return symbolizedInputStack[cursor].get();
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
    int tokenCount = 0; // counts tokens (order in which tokens are produced)

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
            // If the previous token was a number or a closing parenthesis,
            // insert an implicit multiplication.
            if (!symbolizedInputStack.empty()) {
                Symbol* lastToken = symbolizedInputStack.back().get();
                int tokenType = *lastToken;
                if (tokenType == VALUE || tokenType == CLOSINGPARENTHESIS) {
                    cout << "Notice: Implicit multiplication detected. Inserting '*' before '('\n";
                    symbolizedInputStack.push_back(make_unique<Multiplication>());
                    tokenCount++;
                }
            }
            symbolizedInputStack.push_back(make_unique<OpeningParenthesis>());
            tokenCount++;
            parenCount++;
            i++;
            continue;
        }
        else if (c == ')') {
            // Check for empty parentheses: if the previous token is an opening parenthesis.
            if (!symbolizedInputStack.empty() && ((int)*symbolizedInputStack.back().get() == OPENINGPARENTHESIS)) {
                throw runtime_error("Syntax error: Empty parentheses '()' are not allowed at token #"
                                      + to_string(tokenCount + 1) +
                                      ". An expression is expected between '(' and ')'.");
            }
            parenCount--;
            if (parenCount < 0) {
                throw runtime_error("Syntax error: Unmatched closing parenthesis detected at token #"
                                      + to_string(tokenCount + 1) +
                                      ". No corresponding opening parenthesis found.");
            }
            symbolizedInputStack.push_back(make_unique<ClosingParenthesis>());
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
            symbolizedInputStack.push_back(make_unique<Addition>());
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
            symbolizedInputStack.push_back(make_unique<Multiplication>());
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
            symbolizedInputStack.push_back(make_unique<Value>(value));
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
    symbolizedInputStack.push_back(make_unique<End>());
    tokenCount++;
}
