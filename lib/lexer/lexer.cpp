#include <cstddef>
#include <string_view>
#include <vector>

#include "lexer/lexer.hpp"

namespace dragonfly::lexer {
    
inline std::string_view Lexer::next() {
    
}

inline std::string_view Lexer::peek() {
    
}

sinline td::string_view Lexer::current() {
    
}

inline bool Lexer::is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

inline bool Lexer::is_number() {
    return c >= '0' && c <= '9';
}

void Lexer::lex() {
    
}

void Lexer::lex_string() {
    
}

void Lexer::lex_number() {
    
}

void Lexer::lex_identifier() {
    
}

void Lexer::lex_symbol() {
    
}

}  // namespace dragonfly::lexer