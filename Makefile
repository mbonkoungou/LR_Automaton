# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Executable
TARGET = lr_automaton

# Source files
SRCS = Automaton.cpp Lexer.cpp State.cpp Symbol.cpp Main.cpp
OBJS = $(SRCS:.cpp=.o)

# Header files
HEADERS = Automaton.h Lexer.h State.h Symbol.h

# Default target
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f *.o

# Clean everything including the executable
mrproper: clean
	rm -f $(TARGET)
