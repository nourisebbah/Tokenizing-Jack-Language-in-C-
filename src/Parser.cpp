#include "Parser.h"
#include <iostream>

Parser::Parser(Tokenizer& tokenizer, const std::string& outputFilename)
    : tokenizer(tokenizer), vmWriter(outputFilename) {}

void Parser::advance() {
    if (tokenizer.hasMoreTokens()) {
        currentToken = tokenizer.getNextToken();
    }
}

bool Parser::check(const std::string& expected) {
    return currentToken.value == expected;
}

void Parser::expect(const std::string& expected) {
    if (!check(expected)) {
        std::cerr << "Syntax error: Expected " << expected << ", got " << currentToken.value << std::endl;
        exit(1);
    }
    advance();
}

std::string Parser::expectIdentifier() {
    std::string val = currentToken.value;
    if (currentToken.type != "identifier") {
        std::cerr << "Syntax error: Expected identifier, got " << val << std::endl;
        exit(1);
    }
    advance();
    return val;
}

void Parser::parse() {
    advance();
    compileClass();
}

void Parser::compileClass() {
    expect("class");
    className = expectIdentifier();
    expect("{");

    while (check("static") || check("field")) {
        compileClassVarDec();
    }

    while (check("constructor") || check("function") || check("method")) {
        compileSubroutine();
    }

    expect("}");
}

void Parser::compileClassVarDec() {
    advance(); 
    advance(); // type
    expectIdentifier(); 
    while (check(",")) {
        advance();
        expectIdentifier();
    }
    expect(";");
}

void Parser::compileSubroutine() {
    advance(); 
    advance(); // return type
    std::string subroutineName = expectIdentifier();
    expect("(");
    compileParameterList();
    expect(")");

    expect("{");
    while (check("var")) {
        compileVarDec();
    }

    vmWriter.writeFunction(className + "." + subroutineName, 0); 
    compileStatements();
    expect("}");
}

void Parser::compileParameterList() {
    if (currentToken.value != ")") {
        advance(); // type
        expectIdentifier(); // var name
        while (check(",")) {
            advance();
            advance(); // type
            expectIdentifier();
        }
    }
}

void Parser::compileVarDec() {
    expect("var");
    advance(); // type
    expectIdentifier();
    while (check(",")) {
        advance();
        expectIdentifier();
    }
    expect(";");
}

void Parser::compileStatements() {
    while (check("let") || check("if") || check("while") || check("do") || check("return")) {
        if (check("let")) compileLet();
        else if (check("if")) compileIf();
        else if (check("while")) compileWhile();
        else if (check("do")) compileDo();
        else if (check("return")) compileReturn();
    }
}

void Parser::compileLet() {
    expect("let");
    expectIdentifier();
    expect("=");
    compileExpression();
    expect(";");
    vmWriter.writePop("local", 0);
}

void Parser::compileIf() {
    expect("if");
    expect("(");
    compileExpression();
    expect(")");
    expect("{");
    compileStatements();
    expect("}");
}

void Parser::compileWhile() {
    expect("while");
    expect("(");
    compileExpression();
    expect(")");
    expect("{");
    compileStatements();
    expect("}");
}

void Parser::compileDo() {
    expect("do");

   
    std::string className = expectIdentifier();  
    expect(".");  // Expect the dot
    std::string functionName = expectIdentifier();  

    expect("(");  // Expect opening parenthesis
    int nArgs = 0;
    compileExpressionList(nArgs);  // Parse arguments
    expect(")");

    expect(";");  // Expect semicolon
    vmWriter.writeCall(className + "." + functionName, nArgs);  
    vmWriter.writePop("temp", 0);  // Discard return value
}


void Parser::compileReturn() {
    expect("return");
    if (!check(";")) {
        compileExpression();
    }
    expect(";");
    vmWriter.writeReturn();
}

void Parser::compileExpression() {
    compileTerm();
    while (check("+") || check("-") || check("*") || check("/")) {
        std::string op = currentToken.value;
        advance();
        compileTerm();
        if (op == "+") vmWriter.writeArithmetic("add");
        else if (op == "-") vmWriter.writeArithmetic("sub");
        else if (op == "*") vmWriter.writeCall("Math.multiply", 2);
        else if (op == "/") vmWriter.writeCall("Math.divide", 2);
    }
}

void Parser::compileTerm() {
    if (currentToken.type == "integerConstant") {
        vmWriter.writePush("constant", std::stoi(currentToken.value));
        advance();
    } else if (currentToken.type == "stringConstant") { 
        std::string str = currentToken.value;
        vmWriter.writePush("constant", str.length()); 
        vmWriter.writeCall("String.new", 1); 
        for (char c : str) {  
            vmWriter.writePush("constant", (int)c);  
            vmWriter.writeCall("String.appendChar", 2);  
        }
        advance();
    }
    else if (currentToken.type == "stringConstant") {  
        std::string str = currentToken.value;
        vmWriter.writePush("constant", str.length()); 
        vmWriter.writeCall("String.new", 1);  
        for (char c : str) {  
            vmWriter.writePush("constant", (int)c);  
            vmWriter.writeCall("String.appendChar", 2); 
        }
        advance();
    } else if (currentToken.value == "(") {
        advance();
        compileExpression();
        expect(")");
    } else if (currentToken.type == "identifier") {
        advance(); 
    } else {
        std::cerr << "Unsupported term: " << currentToken.value << std::endl;
        exit(1);
    }
}

void Parser::compileExpressionList(int& nArgs) {
    nArgs = 0;
    if (!check(")")) {
        compileExpression();
        nArgs++;
        while (check(",")) {
            advance();
            compileExpression();
            nArgs++;
        }
    }
}
