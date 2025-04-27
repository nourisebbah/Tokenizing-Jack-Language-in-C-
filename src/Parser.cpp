#include "Parser.h"

Parser::Parser(Tokenizer& tokenizer, const std::string& outputFilename)
    : tokenizer(tokenizer) {
    outputFile.open(outputFilename);
}

void Parser::writeToken(const Token& token) {
    outputFile << "<" << token.type << "> " << token.value << " </" << token.type << ">\n";
}

void Parser::parse() {
    outputFile << "<tokens>\n";
    while (tokenizer.hasMoreTokens()) {
        Token token = tokenizer.getNextToken();
        writeToken(token);
    }
    outputFile << "</tokens>\n";
}
