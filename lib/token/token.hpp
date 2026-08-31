#pragma once

#include <string_view>
#include <unordered_map>

namespace dragonfly::lexer {

enum class TokenType {
    END_OF_FILE,  

    // Values
    NUMBER,      // 123456789
    FLOAT,       // 3.14
    IDENTIFIER,  // abc123_
    STRING,      // "..."  
    CHAR,        // '.'  

    PLUS,   // +
    MINUS,  // -
    DIVIDE, // /
    STAR,   // *
    DOT,    // .

    OPEN_PARAM,          // (
    CLOSE_PARAM,         // )
    OPEN_SQUARE_PARAM,   // [
    CLOSE_SQUARE_PARAM,  // ]
    OPEN_BRACES,         // {
    CLOSE_BRACES,        // }

    AT_SYMBOL,      // @
    COLON,          // :
    COLON_EQUALS,   // :=
    DOUBLE_COLON,   // ::
    TILDE,          // ~
    COMMA,          // ,
    SEMICOLON,      // ;

    EQUALS,                // =
    EQUALS_EQUALS,         // ==
    NOT,                   // !
    NOT_EQUALS,            // !=
    GREATER_THAN,          // >
    GREATER_EQUAL,         // >=
    LESS_THAN,             // <
    LESS_EQUAL,            // <=
    AMPERSAND_AMPERSAND,   // &&
    PIPE_PIPE,             // ||
    CARET,                 // ^
};

class Token {
public:
    TokenType type;
    std::string_view value;
    int line;
    int column;

    Token(std::string_view value, TokenType type, int line, int column)
        : type(type), value(value), line(line), column(column) {}
};

std::unordered_map<std::string_view, Token> TokenSymbolLookUp = {
    {'', Token}
}

} 