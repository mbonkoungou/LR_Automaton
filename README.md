# LR_Automaton

This project implements a simple **LR parser** (bottom-up parser) for arithmetic expressions, written in C++. It parses and evaluates expressions containing:

- **Numeric values** (including decimals)  
- **Parentheses** `(` and `)`  
- **Plus** `+`  
- **Multiplication** `*`  
- **Implicit multiplication** (e.g., `2(3+4)` or `(1+2)(3+4)`)

In addition to evaluating the arithmetic result, the program **prints the syntax tree** of the final expression if the parse succeeds.

## Features

1. **Lexer**  
   - Splits the input string into tokens (symbols).  
   - Handles numbers, operators (`+`, `*`), parentheses, and end-of-input.  
   - Detects whitespace and syntax errors (unmatched parentheses, illegal characters, etc.).

2. **States & Automaton**  
   - A hand-crafted LR automaton with multiple state classes.  
   - The `Automaton` manages the stack of states and symbols, performing shifts and reductions as needed.

3. **Error Handling**  
   - Descriptive error messages if parsing fails (e.g., unmatched parentheses).

4. **Expression Evaluation & Tree Printing**  
   - On success, the parser returns an `Expr` object that is evaluated.  
   - **Prints the arithmetic result** and **the syntax tree** in a textual format.


## Building

You need a C++ compiler supporting at least C++11.

1. Open a terminal in the project root directory.  
2. Run the following command to build:

   ```bash
   make
   ```

   This generates an executable named `lr_automaton` (or `lr_automaton.exe` on Windows).

Alternatively, compile manually:

```bash
g++ -std=c++11 -Wall -Wextra Automaton.cpp Lexer.cpp State.cpp Symbol.cpp Main.cpp -o lr_automaton
```

## Running

Once built, run:

```bash
./lr_automaton
```

(Windows users might need `.\lr_automaton.exe`.)

1. The program prompts for an expression:
   ```
   Enter the expression to analyze:
   ```
2. Type an arithmetic expression, e.g.:
   ```
   (2 + 3) * (4 + 5)
   ```
3. If parsed successfully:
   - **The result** of the expression is printed.  
   - **The syntax tree** is printed in a textual form.

Example output:

```
Result = 45

Final Syntax Tree:
<Printed syntax tree structure here>
```

If there is a syntax error (like `3++4` or `(2+3` missing a closing parenthesis), the program prints an error message and exits.

## Usage Notes & Examples

- **Basic arithmetic:**  
  - `3+4`, `2*5+1`, `(10+2)*3.5`
- **Implicit multiplication:**  
  - `2(3+4)` → Interpreted as `2 * (3+4)`.  
  - `(2+1)(3+4)` → Interpreted as `(2+1) * (3+4)`.
- **Error handling:**  
  - `3++4` or `(2+3` triggers syntax error messages detailing the location of the error.

## Customizing or Extending

1. Update **Lexer** (`Lexer.cpp`) for new token types or operators.  
2. Modify or add **States** (`State.cpp` / `State.h`) to handle new grammar rules.  
3. Extend **Symbol** (`Symbol.cpp` / `Symbol.h`) with new token classes or AST node types (e.g., `-`, `/`, exponentiation).

