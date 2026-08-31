#include <cstddef>
#include <string_view>
#include <vector>
#include <iostream>
#include <cctype>

#include "lexer/lexer.hpp"

namespace dragonfly::lexer {

// Returns the next character in the input and advances the position
inline unsigned char Lexer::next() {
    pos += 1;
    column += 1;
    if (current() == '\n') {
        line += 1;
        column = 1;
    }
    return current();
}

// Returns the next character in the input without advancing the position
inline unsigned char Lexer::peek() {
    return code[pos + 1];
}

inline unsigned char Lexer::current() {
    return code[pos];
}

// NOTE: \n is handled in next() because we need to update the line counter
inline bool Lexer::is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\r';
}

inline bool Lexer::is_number(char c) {
    return c >= '0' && c <= '9';
}

void Lexer::lex() {
    char c = current();
    while (c != '\0') {
        if (is_whitespace(c)) {
            next();
        } else if (c == '\n') {
            next();
        } else if (is_number(c)) {
            lex_number();
        } else if (isalpha(c) || c == '_') {
            lex_identifier();
        } else if (c == '"') {
            lex_string();
        } else if (c =='\'') {
            lex_char();
        } else {
            lex_symbol();
        }
        c = current();
    }
    tokens.emplace_back("", TokenType::END_OF_FILE, line, column);
}

void Lexer::lex_string() {
    std::string_view str;
    next(); // "
    std::size_t start_pos = pos;
    while (current() != '"' && current() != '\0') {
        next();
    }
    str = code.substr(start_pos, pos - start_pos);
    next(); // "
    tokens.emplace_back(str, TokenType::STRING, line, column);
}

void Lexer::lex_char() {
    std::string_view chr;
    next();
    std::size_t start_pos = pos;
    while (current() != '\'' && current() != '\0') {
        next();
    }
    chr = code.substr(start_pos, pos - start_pos);
    next(); 
    tokens.emplace_back(chr, TokenType::CHAR, line, column);
}

void Lexer::lex_number() {
    std::string_view number;
    std::size_t start_pos = pos;
    while (is_number(current())) {
        next();
    }
    if (current() == '.') {
        next(); 
        while (is_number(current())) {
            next();
        }
        number = code.substr(start_pos, pos - start_pos);
        tokens.emplace_back(number, TokenType::FLOAT, line, column);
    } else {
        number = code.substr(start_pos, pos - start_pos);
        tokens.emplace_back(number, TokenType::NUMBER, line, column);
    }
}

void Lexer::lex_identifier() {
    std::string_view identifier;
    std::size_t start_pos = pos;
    while (std::isalnum(current()) || current() == '_') {
        next();
    }
    // std::cout << "start_pos: " << start_pos << ", pos: " << pos << std::endl;
    identifier = code.substr(start_pos, pos - start_pos);
    // std::cout << "Lexed identifier: '" << identifier << "' at line " << line << ", column " << column << std::endl;
    tokens.emplace_back(identifier, TokenType::IDENTIFIER, line, column);
}

void Lexer::lex_symbol() {
    switch (current()) {
        case '+':
            tokens.emplace_back("+", TokenType::PLUS, line, column);
            break;
        case '-':
            tokens.emplace_back("-", TokenType::MINUS, line, column);
            break;
        case '*':
            tokens.emplace_back("*", TokenType::STAR, line, column);
            break;
        case '/':
            tokens.emplace_back("/", TokenType::DIVIDE, line, column);
            break;

        case '.':
            tokens.emplace_back(".", TokenType::DOT, line, column);
            break;
        case '(':
            tokens.emplace_back("(", TokenType::OPEN_PARAM, line, column);
            break;
        case ')':
            tokens.emplace_back(")", TokenType::CLOSE_PARAM, line, column);
            break;
        case '[':
            tokens.emplace_back("[", TokenType::OPEN_SQUARE_PARAM, line, column);
            break;
        case ']':
            tokens.emplace_back("]", TokenType::CLOSE_SQUARE_PARAM, line, column);
            break;
        case '{':
            tokens.emplace_back("{", TokenType::OPEN_BRACES, line, column);
            break;
        case '}':
            tokens.emplace_back("}", TokenType::CLOSE_BRACES, line, column);
            break;

        case '@':
            tokens.emplace_back("@", TokenType::AT_SYMBOL, line, column);
            break;
        case ':':
            if (peek() == '=') {
                tokens.emplace_back(":=", TokenType::COLON_EQUALS, line, column);
                next(); 
            } else if (peek() == ':') {
                tokens.emplace_back("::", TokenType::DOUBLE_COLON, line, column);
                next(); 
            } else {
                tokens.emplace_back(":", TokenType::COLON, line, column);
            }
            break;
        case '~':
            tokens.emplace_back("~", TokenType::TILDE, line, column);
            break;
        case ',':
            tokens.emplace_back(",", TokenType::COMMA, line, column);
            break;
        case ';':
            tokens.emplace_back(";", TokenType::SEMICOLON, line, column);
            break;
        case '=':
            if (peek() == '=') {
                tokens.emplace_back("==", TokenType::EQUALS_EQUALS, line, column);
                next(); 
            } else {
                tokens.emplace_back("=", TokenType::EQUALS, line, column);
            }
            break;
        case '!':
            if (peek() == '=') {
                tokens.emplace_back("!=", TokenType::NOT_EQUALS, line, column);
                next(); 
            } else {
                tokens.emplace_back("!", TokenType::NOT, line, column);
            }
            break;
        case '>':
            if (peek() == '=') {
                tokens.emplace_back(">=", TokenType::GREATER_EQUAL, line, column);
                next();
            } else {
                tokens.emplace_back(">", TokenType::GREATER_THAN, line, column);
            }
            break;
        case '<':
            if (peek() == '=') {
                tokens.emplace_back("<=", TokenType::LESS_EQUAL, line, column);
                next();  
            } else {
                tokens.emplace_back("<", TokenType::LESS_THAN, line, column);
            }
            break;
        case '&':
            if (peek() == '&') {
                tokens.emplace_back("&&", TokenType::AMPERSAND_AMPERSAND, line, column);
                next();  
            } else {
                tokens.emplace_back("&", TokenType::AMPERSAND, line, column);
            }
            break;
        case '|':
            if (peek() == '|') {
                tokens.emplace_back("||", TokenType::PIPE_PIPE, line, column);
                next();  
            } else {
                tokens.emplace_back("|", TokenType::PIPE, line, column);
            }
            break;
        case '^':
            tokens.emplace_back("^", TokenType::CARET, line, column);
            break;
        default:
            // Handle unknown symbols or throw an error
            tokens.emplace_back(std::string(1, current()), TokenType::UNKNOWN, line, column);
            break;
    }
    next();
}

}  // namespace dragonfly::lexer