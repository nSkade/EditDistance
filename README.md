# EditDistance
a simple implementation of edit distance algorithms using C++ std::string, written in a functional programming style.
This was done for an assignment in 2020 and used to learn basics of C++.

## functionalities
* calculation of the edit distance matrix
* calculation of needed operations from a matrix (backtrace)
* support for swapping two following characters (Twiddle)
* step by step word creation from existing or empty word
* print matrix with colors (linux and windows)

## usage
* compile with make (define compiler in makefile)
* in command line EditDistance $initial word$ $word to change to$

## TODO
* put functions in a class/library
* add guards
* custiom operation costs
