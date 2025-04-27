
# JackAnalyzer – Project 10
# This project is part of my Nand2Tetris journey [Project 10], where the goal was to build a Jack Tokenizer and a basic Parser.

 Take .jack source files ➔ break them into tokens ➔ and output a structured .xml file showing the tokenized version of the code.
 
# 1.  main.cpp :
The program starts with a basic main(argc, argv) function.
You pass the path to a folder containing .jack files as an argument when running the program.

Example:

./JackAnalyzer jack_files/

It checks if the right number of arguments are given. If not, it tells you how to use it.
Then it loops through all files inside the folder

For every .jack file it finds:

It creates a Tokenizer (to break the file into tokens),
Creates a Parser (to output them into an XML file),
Then calls parse() to do the rest.

# 2. Tokenizing (Tokenizer.h and Tokenizer.cpp)

Tokenizer is a class that:

Reads the entire .jack file into a string.
Breaks that string into tokens:
Keywords like class, if, else, etc.
Identifiers (names like myVar, doSomething).
Integer constants (numbers).
String constants ("hello world").
Symbols ({}, (), ;, etc.)

Some  C++ cool stuff used here:

std::unordered_set to quickly check if something is a keyword.

Some helper functions like isspace, isalpha, isdigit to detect different types of characters.

Functions inside Tokenizer:

Tokenizer(filename): Load file and start tokenizing.

hasMoreTokens(): Are there still tokens left?

getNextToken(): Get the next token!

# 3. Parsing (Parser.h and Parser.cpp)

Parser is a class that:

Takes a Tokenizer and an output filename.

Opens the output file.

Writes all tokens between <tokens> and </tokens> tags in XML.


Functions inside Parser:

Parser(tokenizer, outputFilename): Setup.
parse(): Loop through all tokens and output them.
writeToken(token): Helper to write one token .


# This is just the Tokenizer + basic Parser part!

 Later, the parser will become smarter to (not just print tokens).
If you spot any mistakes or ideas to improve, feel free to open an issue .

