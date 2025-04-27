#include <iostream>
#include <filesystem>
#include "Tokenizer.h"
#include "Parser.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <path_to_jack_files>" << endl;
        return 1;
    }

    string inputPath = argv[1];

    for (const auto& entry : fs::directory_iterator(inputPath)) {
        if (entry.path().extension() == ".jack") {
            string inputFile = entry.path().string();
            string outputFile = "output/" + entry.path().stem().string() + ".xml";

            Tokenizer tokenizer(inputFile);
            Parser parser(tokenizer, outputFile);
            parser.parse();
        }
    }

    return 0;
}
