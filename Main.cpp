#include <iostream>
#include <Symbol.h>
#include <Lexer.h>
#include <State.h>
#include <Automaton.h>

using namespace std;

int main() {
    string expression;
    cout << "Enter the expression to analyze: ";
    getline(cin, expression);

    try {
        Automaton* automaton = new Automaton(expression);
        automaton->Analysis();
        delete automaton;
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
