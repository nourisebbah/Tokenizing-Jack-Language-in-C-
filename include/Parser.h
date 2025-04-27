#ifndef PARSER_H
#define PARSER_H

#include "Tokenizer.h"
#include <fstream>

class Parser {
private:
    Tokenizer& tokenizer;
    std::ofstream outputFile;

    void writeToken(const Token& token);

public:
    Parser(Tokenizer& tokenizer, const std::string& outputFilename);
    void parse();
};

#endif // PARSER_H
