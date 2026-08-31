#include <gtest/gtest.h>

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "lexer/lexer.hpp"
#include "helpers.hpp"

// Combined tests combine all other tests (identifiers, literals, symbols)
// using longer statements and expressions, taken from the language spec.

using namespace dragonfly::lexer;
using namespace dragonfly::lexer::test;

TokenType bracket_type_for(char c) {
    switch (c) {
        case '(': return TokenType::OPEN_PARAM;
        case ')': return TokenType::CLOSE_PARAM;
        case '[': return TokenType::OPEN_SQUARE_PARAM;
        case ']': return TokenType::CLOSE_SQUARE_PARAM;
        case '{': return TokenType::OPEN_BRACES;
        case '}': return TokenType::CLOSE_BRACES;
        default: throw std::invalid_argument("not a bracket character");
    }
}

TEST(LexerCombined, MathsExpression) {
    std::string input = "x = (x + 5) * (500 / 5) / -4 + 3.9998";
    auto tokens = lex_all(input);
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "x"},
        {TokenType::EQUALS, "="},
        {TokenType::OPEN_PARAM, "("},
        {TokenType::IDENTIFIER, "x"},
        {TokenType::PLUS, "+"},
        {TokenType::NUMBER, "5"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::STAR, "*"},
        {TokenType::OPEN_PARAM, "("},
        {TokenType::NUMBER, "500"},
        {TokenType::DIVIDE, "/"},
        {TokenType::NUMBER, "5"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::DIVIDE, "/"},
        {TokenType::MINUS, "-"},   // unary minus: lexer emits MINUS then NUMBER,
        {TokenType::NUMBER, "4"},  // the parser is what decides it's unary - hrs
        {TokenType::PLUS, "+"},
        {TokenType::FLOAT, "3.9998"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, BooleanExpression) {
    auto tokens = lex_all("x = 0 || (1 ^ 1 && ~0) == 0 > 1 < 5 <= 100 >= 500");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "x"},
        {TokenType::EQUALS, "="},
        {TokenType::NUMBER, "0"},
        {TokenType::PIPE_PIPE, "||"},
        {TokenType::OPEN_PARAM, "("},
        {TokenType::NUMBER, "1"},
        {TokenType::CARET, "^"},
        {TokenType::NUMBER, "1"},
        {TokenType::AMPERSAND_AMPERSAND, "&&"},
        {TokenType::TILDE, "~"},
        {TokenType::NUMBER, "0"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::EQUALS_EQUALS, "=="},
        {TokenType::NUMBER, "0"},
        {TokenType::GREATER_THAN, ">"},
        {TokenType::NUMBER, "1"},
        {TokenType::LESS_THAN, "<"},
        {TokenType::NUMBER, "5"},
        {TokenType::LESS_EQUAL, "<="},
        {TokenType::NUMBER, "100"},
        {TokenType::GREATER_EQUAL, ">="},
        {TokenType::NUMBER, "500"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, VariableDeclaration) {
    auto tokens = lex_all("x : i32");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "x"},
        {TokenType::COLON, ":"},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, VariableDeclarationLongName) {
    auto tokens = lex_all("hEllO_210312903_dfsfFJDSIFJ : i32");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "hEllO_210312903_dfsfFJDSIFJ"},
        {TokenType::COLON, ":"},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, VariableDeclarationLongType) {
    auto tokens = lex_all("a : SomeRandomType123_hahaha");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "a"},
        {TokenType::COLON, ":"},
        {TokenType::IDENTIFIER, "SomeRandomType123_hahaha"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, VariableDefinition) {
    auto tokens = lex_all("a : i32 = 100");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "a"},
        {TokenType::COLON, ":"},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::EQUALS, "="},
        {TokenType::NUMBER, "100"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, VariableWalrusInteger) {
    auto tokens = lex_all("a := 1000");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "a"},
        {TokenType::COLON_EQUALS, ":="},
        {TokenType::NUMBER, "1000"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, VariableWalrusString) {
    auto tokens = lex_all("a := \"Hello, World\"");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "a"},
        {TokenType::COLON_EQUALS, ":="},
        {TokenType::STRING, "Hello, World"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, VariableWalrusChar) {
    auto tokens = lex_all("a := 'a'");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "a"},
        {TokenType::COLON_EQUALS, ":="},
        {TokenType::CHAR, "a"}, 
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, AllTypes) {
    auto tokens = lex_all("u8 u16 u32 u64 i8 i16 i32 i64 f16 f32 f64");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "u8"},
        {TokenType::IDENTIFIER, "u16"},
        {TokenType::IDENTIFIER, "u32"},
        {TokenType::IDENTIFIER, "u64"},
        {TokenType::IDENTIFIER, "i8"},
        {TokenType::IDENTIFIER, "i16"},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::IDENTIFIER, "i64"},
        {TokenType::IDENTIFIER, "f16"},
        {TokenType::IDENTIFIER, "f32"},
        {TokenType::IDENTIFIER, "f64"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, HolyBrackets) {
    // This used to be more but I gave up and made it short ;-;
    auto tokens = lex_all("([{([])}])");
    expect_tokens(tokens, {
        {TokenType::OPEN_PARAM, "("},
        {TokenType::OPEN_SQUARE_PARAM, "["},
        {TokenType::OPEN_BRACES, "{"},
        {TokenType::OPEN_PARAM, "("},
        {TokenType::OPEN_SQUARE_PARAM, "["},
        {TokenType::CLOSE_SQUARE_PARAM, "]"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::CLOSE_BRACES, "}"},
        {TokenType::CLOSE_SQUARE_PARAM, "]"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, Tuple) {
    auto tokens = lex_all("point2d : (i32, i32)");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "point2d"},
        {TokenType::COLON, ":"},
        {TokenType::OPEN_PARAM, "("},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::COMMA, ","},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, TupleWithAssignment) {
    constexpr std::string_view source = R"(point2d : (i32, i32)
        point2d[0] = 1)";

    auto tokens = lex_all(source);

    for (const auto& token : tokens) {
        std::cout << "Token: " << token.value << " (type: " << static_cast<int>(token.type) << ") at line " << token.line << ", column " << token.column << std::endl;
    }

    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "point2d"},
        {TokenType::COLON, ":"},
        {TokenType::OPEN_PARAM, "("},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::COMMA, ","},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::IDENTIFIER, "point2d"},
        {TokenType::OPEN_SQUARE_PARAM, "["},
        {TokenType::NUMBER, "0"},
        {TokenType::CLOSE_SQUARE_PARAM, "]"},
        {TokenType::EQUALS, "="},
        {TokenType::NUMBER, "1"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, Array) {
    auto tokens = lex_all("numbers : [i32; 5]");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "numbers"},
        {TokenType::COLON, ":"},
        {TokenType::OPEN_SQUARE_PARAM, "["},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::SEMICOLON, ";"},
        {TokenType::NUMBER, "5"},
        {TokenType::CLOSE_SQUARE_PARAM, "]"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, ArrayWithAssignment) {
    constexpr std::string_view source = R"(numbers : [i32; 5]
        numbers[0] = 100
        numbers[2] = 32480)";

    auto tokens = lex_all(source);
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "numbers"},
        {TokenType::COLON, ":"},
        {TokenType::OPEN_SQUARE_PARAM, "["},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::SEMICOLON, ";"},
        {TokenType::NUMBER, "5"},
        {TokenType::CLOSE_SQUARE_PARAM, "]"},
        {TokenType::IDENTIFIER, "numbers"},
        {TokenType::OPEN_SQUARE_PARAM, "["},
        {TokenType::NUMBER, "0"},
        {TokenType::CLOSE_SQUARE_PARAM, "]"},
        {TokenType::EQUALS, "="},
        {TokenType::NUMBER, "100"},
        {TokenType::IDENTIFIER, "numbers"},
        {TokenType::OPEN_SQUARE_PARAM, "["},
        {TokenType::NUMBER, "2"},
        {TokenType::CLOSE_SQUARE_PARAM, "]"},
        {TokenType::EQUALS, "="},
        {TokenType::NUMBER, "32480"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, FunctionDeclaration) {
    auto tokens = lex_all("add : (i32, i32) i32");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "add"},
        {TokenType::COLON, ":"},
        {TokenType::OPEN_PARAM, "("},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::COMMA, ","},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, FunctionDeclarationWithNamedArgs) {
    auto tokens = lex_all("add : (x: i32, y: i32) i32");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "add"},
        {TokenType::COLON, ":"},
        {TokenType::OPEN_PARAM, "("},
        {TokenType::IDENTIFIER, "x"},
        {TokenType::COLON, ":"},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::COMMA, ","},
        {TokenType::IDENTIFIER, "y"},
        {TokenType::COLON, ":"},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, FunctionDefinitionAndAssignment) {
    auto tokens = lex_all("add : (x: i32, y: i32) i32 = (x, y) { x + y }");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "add"},
        {TokenType::COLON, ":"},
        {TokenType::OPEN_PARAM, "("},
        {TokenType::IDENTIFIER, "x"},
        {TokenType::COLON, ":"},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::COMMA, ","},
        {TokenType::IDENTIFIER, "y"},
        {TokenType::COLON, ":"},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::IDENTIFIER, "i32"},
        {TokenType::EQUALS, "="},
        {TokenType::OPEN_PARAM, "("},
        {TokenType::IDENTIFIER, "x"},
        {TokenType::COMMA, ","},
        {TokenType::IDENTIFIER, "y"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::OPEN_BRACES, "{"},
        {TokenType::IDENTIFIER, "x"},
        {TokenType::PLUS, "+"},
        {TokenType::IDENTIFIER, "y"},
        {TokenType::CLOSE_BRACES, "}"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerCombined, ControlFlow) {
    auto tokens = lex_all("(i <= 40) { 5 } : (i > 100) { 1 } : { 0 }");
    expect_tokens(tokens, {
        {TokenType::OPEN_PARAM, "("},
        {TokenType::IDENTIFIER, "i"},
        {TokenType::LESS_EQUAL, "<="},
        {TokenType::NUMBER, "40"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::OPEN_BRACES, "{"},
        {TokenType::NUMBER, "5"},
        {TokenType::CLOSE_BRACES, "}"},
        {TokenType::COLON, ":"},
        {TokenType::OPEN_PARAM, "("},
        {TokenType::IDENTIFIER, "i"},
        {TokenType::GREATER_THAN, ">"},
        {TokenType::NUMBER, "100"},
        {TokenType::CLOSE_PARAM, ")"},
        {TokenType::OPEN_BRACES, "{"},
        {TokenType::NUMBER, "1"},
        {TokenType::CLOSE_BRACES, "}"},
        {TokenType::COLON, ":"},
        {TokenType::OPEN_BRACES, "{"},
        {TokenType::NUMBER, "0"},
        {TokenType::CLOSE_BRACES, "}"},
        {TokenType::END_OF_FILE, ""},
    });
}