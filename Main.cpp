#include <iostream>
#include <Symbol.h>
#include <Lexer.h>
#include <State.h>
#include <Automaton.h>

using namespace std;

int main() {
    string expression;
    
    cout << "Enter the expression to analyze: ";
    cin >> expression;

    Automaton* automaton = new Automaton(expression);
    automaton->analysis();
    
    delete automaton;
    return 0;
}
