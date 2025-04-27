#include "Tokenizer.h"
#include <fstream>
#include <cctype>
#include <unordered_set>

Tokenizer::Tokenizer(const std::string& filename) : position(0) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        sourceCode += line + '\n';
    }
    tokenize();
}

// Define a set of Jack keywords
std::unordered_set<std::string> keywords = {
    "class", "constructor", "function", "method", "field", "static", "var", 
    "int", "char", "boolean", "void", "true", "false", "null", "this", 
    "let", "do", "if", "else", "while", "return"
};

void Tokenizer::tokenize() {
    while (position < sourceCode.length()) {
        if (isspace(sourceCode[position])) {
            position++;
            continue;
        }

        if (isalpha(sourceCode[position]) || sourceCode[position] == '_') {
            std::string identifier;
            while (isalnum(sourceCode[position]) || sourceCode[position] == '_') {
                identifier += sourceCode[position++];
            }
            if (keywords.find(identifier) != keywords.end()) {
                tokens.push_back({"keyword", identifier}); // Treat it as a keyword
            } else {
                tokens.push_back({"identifier", identifier}); // Treat it as an identifier
            }
        }
        else if (isdigit(sourceCode[position])) {
            std::string number;
            while (isdigit(sourceCode[position])) {
                number += sourceCode[position++];
            }
            tokens.push_back({"integerConstant", number});
        }
        else if (sourceCode[position] == '"') { // Handle string constants
            std::string strConstant;
            position++; // skip the opening quote
            while (sourceCode[position] != '"' && position < sourceCode.length()) {
                strConstant += sourceCode[position++];
            }
            position++; // skip the closing quote
            tokens.push_back({"stringConstant", strConstant});
        }
        else {
            std::string symbol(1, sourceCode[position++]);
            tokens.push_back({"symbol", symbol});
        }
    }
}

Token Tokenizer::getNextToken() {
    Token token = tokens.front();
    tokens.erase(tokens.begin());
    return token;
}

bool Tokenizer::hasMoreTokens() {
    return !tokens.empty();
}
