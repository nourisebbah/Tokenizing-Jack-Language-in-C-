#include "VMWriter.h"

VMWriter::VMWriter(const std::string& filename) {
    vmFile.open(filename);
}

VMWriter::~VMWriter() {
    if (vmFile.is_open()) {
        vmFile.close();
    }
}

void VMWriter::writePush(const std::string& segment, int index) {
    vmFile << "push " << segment << " " << index << "\n";
}

void VMWriter::writePop(const std::string& segment, int index) {
    vmFile << "pop " << segment << " " << index << "\n";
}

void VMWriter::writeArithmetic(const std::string& command) {
    vmFile << command << "\n";
}

void VMWriter::writeLabel(const std::string& label) {
    vmFile << "label " << label << "\n";
}

void VMWriter::writeGoto(const std::string& label) {
    vmFile << "goto " << label << "\n";
}

void VMWriter::writeIf(const std::string& label) {
    vmFile << "if-goto " << label << "\n";
}

void VMWriter::writeCall(const std::string& name, int nArgs) {
    vmFile << "call " << name << " " << nArgs << "\n";
}

void VMWriter::writeFunction(const std::string& name, int nLocals) {
    vmFile << "function " << name << " " << nLocals << "\n";
}

void VMWriter::writeReturn() {
    vmFile << "return\n";
}
