#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include "Token.h"

class Tokenizer {
private:
    std::string sourceCode;
    size_t position;
    std::vector<Token> tokens;

    void tokenize();

public:
    Tokenizer(const std::string& filename);
    Token getNextToken();
    bool hasMoreTokens();
};

#endif // TOKENIZER_H
