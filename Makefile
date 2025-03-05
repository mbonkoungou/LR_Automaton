# Default target
all: lr_automaton

# Link object files to create the executable
lr_automaton: automaton.o lexer.o state.o symbol.o main.o
	g++ -o lr_automaton lexer.o symbol.o state.o automaton.o main.o

# Compile Automaton.cpp to automaton.o
automaton.o: Automaton.cpp Automaton.h
	g++ -o automaton.o -c Automaton.cpp

# Compile lexer.cpp to lexer.o
lexer.o: Lexer.cpp Lexer.h
	g++ -o lexer.o -c Lexer.cpp

# Compile State.cpp to state.o
state.o: State.cpp State.h
	g++ -o state.o -c State.cpp

# Compile symbole.cpp to symbole.o
symbol.o: Symbol.cpp Symbol.h
	g++ -o symbol.o -c Symbol.cpp

# Compile main.cpp to main.o
main.o: Main.cpp Symbol.h Lexer.h State.h
	g++ -o main.o -c Main.cpp

# Clean target to remove object files
clean:
	rm -rf *.o

# Mrproper target to clean everything, including the executable
mrproper: clean
	rm -rf analyse
