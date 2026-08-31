#pragma once

#include <string>
#include "token/token.hpp"

using namespace dragonfly::lexer;

namespace dragonfly::lexer {

class Lexer {
    private:
        std::string_view code;
        std::vector<Token>& tokens;

        int pos = 0;
        int line = 1;
        int column = 1;

    public: 
        Lexer(std::string_view code, std::vector<Token>& tokens) : code(code), tokens(tokens) {};

        inline unsigned char next(); 
        inline unsigned char peek();
        inline unsigned char current();

        inline bool is_whitespace(char c);
        inline bool is_number(char c);
        
        void lex();
        void lex_string();
        void lex_char();
        void lex_number();
        void lex_identifier();
        void lex_symbol();
};

}