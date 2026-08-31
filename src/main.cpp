#include <iostream>
#include <fstream>
#include "lexer/lexer.hpp"
#include "token/token.hpp"

void compile(const char* filename) {
    std::fstream file(filename, std::ios::in);
    if (file.is_open()) {
        std::cout << "Compiling file: " << filename << std::endl;
        
        std::string code;

        // Read the file content into the string
        code.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        if (code.empty()) {
            std::cout << "Error: File is empty" << std::endl;
            file.close();
            return;
        }
        
        std::vector<Token> tokens;

        Lexer lexer(code, tokens);
        lexer.lex();

        for (const auto& token : tokens) {
            std::cout << "Token: " << token.value << ", Type: " << static_cast<int>(token.type) << ", Line: " << token.line << ", Column: " << token.column << std::endl;
        }

        file.close();
    } else {
        std::cout << "Error: Could not open file " << filename << std::endl;
    }
}

int main(int argc, char** args) {
    switch (argc) {
        case 1:
            std::cout << "Usage: df [filename]" << std::endl;
            break;
        case 2:
            compile(args[1]);
            break;
        default:
            std::cout << "Multiple arguments provided. Please provide a single filename." << std::endl;
            break;
    }

    return 0;
}