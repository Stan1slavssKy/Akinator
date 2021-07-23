#==========================================================================================

# Makefile for akinator_project
#		author: Kurnevich Stanislav

#==========================================================================================

CXX       = g++
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

VALGRIND_FLAGS = --leak-check=full

AKINATOR_DIR = ./akinator
TREE_DIR	 = ./tree
LIBS_DIR     = ./libs
	 
SOURCE = $(AKINATOR_DIR)/main.cpp $(AKINATOR_DIR)/akinator.cpp $(TREE_DIR)/tree.cpp $(LIBS_DIR)/Onegin.cpp $(LIBS_DIR)/stack.cpp $(LIBS_DIR)/protection.cpp
OBJECT = $(SOURCE:.cpp=.o)
OUTPUT = Akinator

default: valgrind

valgrind: $(OUTPUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUTPUT) "base"

launch: $(OUTPUT)
	./$(OUTPUT) "base"

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

main.o: $(AKINATOR_DIR)/main.cpp
	$(CXX) -c $^

akinator.o: $(AKINATOR_DIR)/akinator.cpp 
	$(CXX) -c $^

tree.o: $(TREE_DIR)/tree.cpp
	$(CXX) -c $^

Onegin.o: $(LIBS_DIR)/Onegin.cpp
	$(CXX) -c $^

stack.o: $(LIBS_DIR)/stack.cpp
	$(CXX) -c $^

protection.o: $(LIBS_DIR)/protection.cpp
	$(CXX) -c $^
	
clean:
	rm -f *.o *.a $(OBJECT) $(OUTPUT)

#==========================================================================================