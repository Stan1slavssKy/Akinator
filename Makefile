#--------------------------------------------------------------------------------------

# Makefile for akinator_project
#		author: Kurnevich Stanislav

#--------------------------------------------------------------------------------------

CXX       = g++
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

VALGRIND_FLAGS = --leak-check=full

AKINATOR_DIR = ../akinator
TREE_DIR	 = ../tree

SOURCE = $(AKINATOR_DIR)/main.cpp $(AKINATOR_DIR)/akinator.cpp $(TREE_DIR)/tree.cpp
OBJECT = $(SOURCE:.cpp=.o)
OUTPUT = akinator

default: valgrind

valgrind: $(OUTPUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUTPUT)

launch: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

main.o: $(AKINATOR_DIR)/main.cpp
	$(CXX) -c $^

akinator.o: $(AKINATOR_DIR)/akinator.cpp 
	$(CXX) -c $^

tree.o: $(TREE_DIR)/tree.cpp
	$(CXX) -c $^

clean:
	rm -f *.o *.a $(OUTPUT)

#--------------------------------------------------------------------------------------
