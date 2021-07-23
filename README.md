# Akinator

Current version is for Linux in Russian.

## Usage

All you need to do to use the program:
* To download and install [Graphviz for Linux](https://graphviz.org/download/).
* To download current repository
* Launch this repository:
        
        cd *the folder where you saved the project*
        cd Akinator 
        make launch

There are 4 program modes:
1. Guessing game. 
2. Check the base in graph interpretation.
3. Describing all the properties of an object.
4. Show all differences between two objects in akinator base.

# Compilation

All the code in this directory can be compiled by any IDE (the simplest variant) or using manual compilation. But! Before compiling convert all files from `UTF-8` format to `CP1251`, otherwise the program will say some strange phrases, while text in console is similar to elven letters.

If you find a way to make the program workable (in Russian language) without converting all files to `CP1251` (so with initial `UTF-8` format), comment `#define UTF8_CONV` code-line in `akinator_config.h` file to make the 4th regime of game valid (because in such case there is no any necessarity to convert .dot file to UTF-8 format for graphviz).

Remember that to run the program some base should be exist, so write your initial base or use ready, otherwise you will get an error.
