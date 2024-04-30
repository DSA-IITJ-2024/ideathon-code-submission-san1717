##Lexical Analysis with Trie Structures

#Overview
This project implements a lexical analyzer in C, utilizing Trie data structures for efficient token recognition and keyword matching. The program categorizes tokens such as keywords, operators, integers, floats, character constants, and identifiers from input code.

#Features
Efficient lexical analysis using Trie data structures.
Tokenization and categorization of input code into various token types.
Support for keywords, operators, integers, floats, character constants, special characters, and identifiers.

#Usage
If you have make installed you can run the command "make run"
Orelse compile with this gcc -Wall -Wextra -g -o program main.c trie.c support.c
and for running use this ./program input.txt
View the output in the output.txt file generated by the program.


#Code Structure
lexical_analyzer.c: Main source code file containing the implementation of the lexical analyzer.
support.h and support.c: Header and source files containing functions for token validation and categorization.
trie.h and trie.c: Header and source files containing the implementation of Trie data structures for keyword and operator matching.

#Dependencies
This project relies on standard C libraries (stdio.h, stdlib.h, string.h, ctype.h) for file I/O, memory allocation, string manipulation, and character classification.

