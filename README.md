﻿# EditDistance
a simple implementation of edit distance algorithms using C++ std::string.
This was done for an assignment in 2020 and used to learn basics of C++.

## functionalities
* calculation of the edit distance matrix
* calculation of needed operations from a matrix (Backtrace)
* support for swapping two following characters (Twiddle)
* support for abrupt ending of comparison (Kill)
* step by step word creation from existing or empty word
* print matrix with colors (linux and windows)

## usage
* compile with make (define compiler in makefile)
* in command line EditDistance $initial word$ $word to change to$

## TODO
* custiom operation costs
* put functions in a class/library
* add guards
