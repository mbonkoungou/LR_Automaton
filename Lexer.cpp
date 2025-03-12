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
    int parenCount = 0; // To keep track of opening and closing parentheses

    while (i < inputStream.size()) {
        char c = inputStream[i];
        if (isspace(c)) {
            i++;
            continue;
        }
        // Check for implicit multiplication when an opening parenthesis follows a number or a closing parenthesis.
        if (c == '(') {
            if (!symbolizedInputStack.empty()) {
                Symbol* lastToken = symbolizedInputStack.back();
                int tokenType = *lastToken; // Using the overloaded operator int()
                if (tokenType == VALUE || tokenType == CLOSINGPARENTHESIS) {
                    cout << "Notice: Implicit multiplication detected. Inserting '*' before '('" << endl;
                    symbolizedInputStack.push_back(new Multiplication());
                }
            }
            symbolizedInputStack.push_back(new OpeningParenthesis());
            parenCount++;  // Increase the parenthesis counter.
            i++;
            continue;
        }
        else if (c == ')') {
            symbolizedInputStack.push_back(new ClosingParenthesis());
            parenCount--;  // Decrease the parenthesis counter.
            if (parenCount < 0) {
                throw runtime_error("Error: Too many closing parentheses.");
            }
            i++;
            continue;
        }
        else if (c == '+') {
            // Look ahead for a valid operand after '+'
            size_t j = i + 1;
            while (j < inputStream.size() && isspace(inputStream[j])) j++;
            if (j >= inputStream.size() || ( !isdigit(inputStream[j]) && inputStream[j] != '(')) {
                throw runtime_error("Error: '+' operator missing an operand.");
            }
            symbolizedInputStack.push_back(new Addition());
            i++;
            continue;
        }
        else if (c == '*') {
            // Look ahead for a valid operand after '*'
            size_t j = i + 1;
            while (j < inputStream.size() && isspace(inputStream[j])) j++;
            if (j >= inputStream.size() || ( !isdigit(inputStream[j]) && inputStream[j] != '(')) {
                throw runtime_error("Error: '*' operator missing an operand.");
            }
            symbolizedInputStack.push_back(new Multiplication());
            i++;
            continue;
        }
        else if (isdigit(c)) {
            size_t length = 0;
            while ((i + length) < inputStream.size() && (isdigit(inputStream[i + length]) || inputStream[i + length] == '.')) {
                length++;
            }
            double value = stod(inputStream.substr(i, length));
            symbolizedInputStack.push_back(new Value(value));
            i += length;
            continue;
        }
        else {
            string msg = "Unexpected character: ";
            msg.push_back(c);
            throw runtime_error(msg);
        }
    }
    if (parenCount != 0) {
        throw runtime_error("Error: Unbalanced parentheses in the expression.");
    }
    symbolizedInputStack.push_back(new End());
}