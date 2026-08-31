#include <iostream>
#include <fstream>
#include "lexer.hpp"
#include "token.hpp"

void compile(const char* filename) {
    std::fstream file(filename, std::ios::in);
    if (file.is_open()) {
        std::cout << "Compiling file: " << filename << std::endl;
        
        file.seekg(std::ios::end);
        std::string_view code(file.tellg());
        file.seekg(std::ios::beg);

        if (code.empty()) {
            std::cout << "Error: File is empty" << std::endl;
            file.close();
            return;
        }

        std::vector<Token> tokens;

        Lexer lexer(code, &tokens);

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