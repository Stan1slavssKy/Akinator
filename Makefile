#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for akinator_project
#		author: Kurnevich Stanislav

#--------------------------------------------------------------------------------------

CXX      = g++ -std=c++14
WARNINGS = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 	
RELEASE_MODE = -g0 -Ofast

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all -v

AKINATOR_DIR = ../akinator
TREE_DIR	 = ../tree

SOURCE = $(AKINATOR_DIR)main.cpp $(AKINATOR_DIR)akinator.cpp $(AKINATOR_DIR)tree.cpp
OBJECT = $(ASM_SOURCE:.cpp=.o)
OUTPUT = akinator

default: valgrind

valgrind: $(OUTPUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUTPUT)

launch: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

clean:
	rm -f *.o *.a $(OUTPUT)

#--------------------------------------------------------------------------------------