#ifndef PARSER_H
#define PARSER_H

#include "Tokenizer.h"
#include "VMWriter.h"
#include <string>

class Parser {
private:
    Tokenizer& tokenizer;
    VMWriter vmWriter;
    std::string className;

    Token currentToken;
    void advance();
    bool check(const std::string& expected);
    void expect(const std::string& expected);
    std::string expectIdentifier();

    void compileClass();
    void compileClassVarDec();
    void compileSubroutine();
    void compileParameterList();
    void compileVarDec();
    void compileStatements();
    void compileLet();
    void compileIf();
    void compileWhile();
    void compileDo();
    void compileReturn();
    void compileExpression();
    void compileTerm();
    void compileExpressionList(int& nArgs);

public:
    Parser(Tokenizer& tokenizer, const std::string& outputFilename);
    void parse();
};

#endif
