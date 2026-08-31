#include <gtest/gtest.h>

#include "lexer/lexer.hpp"
#include "helpers.hpp"

using namespace dragonfly::lexer;
using namespace dragonfly::lexer::test;

TEST(LexerSymbols, Plus)   { expect_single_token("+", TokenType::PLUS, "+"); }
TEST(LexerSymbols, Minus)  { expect_single_token("-", TokenType::MINUS, "-"); }
TEST(LexerSymbols, Star)   { expect_single_token("*", TokenType::STAR, "*"); }
TEST(LexerSymbols, Divide) { expect_single_token("/", TokenType::DIVIDE, "/"); }
TEST(LexerSymbols, Dot)    { expect_single_token(".", TokenType::DOT, "."); }

TEST(LexerSymbols, OpenParam)         { expect_single_token("(", TokenType::OPEN_PARAM, "("); }
TEST(LexerSymbols, CloseParam)        { expect_single_token(")", TokenType::CLOSE_PARAM, ")"); }
TEST(LexerSymbols, OpenSquareParam)   { expect_single_token("[", TokenType::OPEN_SQUARE_PARAM, "["); }
TEST(LexerSymbols, CloseSquareParam)  { expect_single_token("]", TokenType::CLOSE_SQUARE_PARAM, "]"); }
TEST(LexerSymbols, OpenBraces)        { expect_single_token("{", TokenType::OPEN_BRACES, "{"); }
TEST(LexerSymbols, CloseBraces)       { expect_single_token("}", TokenType::CLOSE_BRACES, "}"); }

TEST(LexerSymbols, AtSymbol)    { expect_single_token("@", TokenType::AT_SYMBOL, "@"); }
TEST(LexerSymbols, Colon)       { expect_single_token(":", TokenType::COLON, ":"); }
TEST(LexerSymbols, ColonEquals) { expect_single_token(":=", TokenType::COLON_EQUALS, ":="); }
TEST(LexerSymbols, DoubleColon) { expect_single_token("::", TokenType::DOUBLE_COLON, "::"); }
TEST(LexerSymbols, Tilde)       { expect_single_token("~", TokenType::TILDE, "~"); }
TEST(LexerSymbols, Comma)       { expect_single_token(",", TokenType::COMMA, ","); }
TEST(LexerSymbols, Semicolon)   { expect_single_token(";", TokenType::SEMICOLON, ";"); }

TEST(LexerSymbols, Equals)             { expect_single_token("=", TokenType::EQUALS, "="); }
TEST(LexerSymbols, EqualsEquals)       { expect_single_token("==", TokenType::EQUALS_EQUALS, "=="); }
TEST(LexerSymbols, Not)                { expect_single_token("!", TokenType::NOT, "!"); }
TEST(LexerSymbols, NotEquals)          { expect_single_token("!=", TokenType::NOT_EQUALS, "!="); }
TEST(LexerSymbols, GreaterThan)        { expect_single_token(">", TokenType::GREATER_THAN, ">"); }
TEST(LexerSymbols, GreaterEqual)       { expect_single_token(">=", TokenType::GREATER_EQUAL, ">="); }
TEST(LexerSymbols, LessThan)           { expect_single_token("<", TokenType::LESS_THAN, "<"); }
TEST(LexerSymbols, LessEqual)          { expect_single_token("<=", TokenType::LESS_EQUAL, "<="); }
TEST(LexerSymbols, AmpersandAmpersand) { expect_single_token("&&", TokenType::AMPERSAND_AMPERSAND, "&&"); }
TEST(LexerSymbols, Ampersand)          { expect_single_token("&", TokenType::AMPERSAND, "&"); }
TEST(LexerSymbols, PipePipe)           { expect_single_token("||", TokenType::PIPE_PIPE, "||"); }
TEST(LexerSymbols, Pipe)               { expect_single_token("|", TokenType::PIPE, "|"); }
TEST(LexerSymbols, Caret)              { expect_single_token("^", TokenType::CARET, "^"); }


TEST(LexerSymbolsMaximalMunch, ColonEqualsIsOneTokenWhenAdjacent) {
    auto tokens = lex_all(":=");
    expect_tokens(tokens, {
        {TokenType::COLON_EQUALS, ":="},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerSymbolsMaximalMunch, ColonThenEqualsSpaced) {
    auto tokens = lex_all(": =");
    expect_tokens(tokens, {
        {TokenType::COLON, ":"},
        {TokenType::EQUALS, "="},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerSymbolsMaximalMunch, DoubleColonIsOneTokenWhenAdjacent) {
    auto tokens = lex_all("::");
    expect_tokens(tokens, {
        {TokenType::DOUBLE_COLON, "::"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerSymbolsMaximalMunch, DoubleColonSpaced) {
    auto tokens = lex_all(": :");
    expect_tokens(tokens, {
        {TokenType::COLON, ":"},
        {TokenType::COLON, ":"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerSymbolsMaximalMunch, EqualsEqualsIsOneTokenWhenAdjacent) {
    auto tokens = lex_all("==");
    expect_tokens(tokens, {
        {TokenType::EQUALS_EQUALS, "=="},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerSymbolsMaximalMunch, EqualsThenEqualsIsEqualsEquals) {
    auto tokens = lex_all("= =");
    expect_tokens(tokens, {
        {TokenType::EQUALS, "="},
        {TokenType::EQUALS, "="},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerSymbolsMaximalMunch, GreaterEqualIsOneTokenWhenAdjacent) {
    auto tokens = lex_all(">=");
    expect_tokens(tokens, {
        {TokenType::GREATER_EQUAL, ">="},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerSymbolsMaximalMunch, LessEqualIsOneTokenWhenAdjacent) {
    auto tokens = lex_all("<=");
    expect_tokens(tokens, {
        {TokenType::LESS_EQUAL, "<="},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerSymbolsMaximalMunch, NotEqualsIsOneTokenWhenAdjacent) {
    auto tokens = lex_all("!=");
    expect_tokens(tokens, {
        {TokenType::NOT_EQUALS, "!="},
        {TokenType::END_OF_FILE, ""},
    });
}