#include <gtest/gtest.h>

#include "lexer/lexer.hpp"
#include "helpers.hpp"

using namespace dragonfly::lexer;
using namespace dragonfly::lexer::test;

TEST(LexerLiterals, SingleDigit) {
    expect_single_token("5", TokenType::NUMBER, "5");
}

TEST(LexerLiterals, MultiDigit) {
    expect_single_token("12345", TokenType::NUMBER, "12345");
}

TEST(LexerLiterals, Zero) {
    expect_single_token("0", TokenType::NUMBER, "0");
}

TEST(LexerLiterals, LeadingZeros) {
    expect_single_token("007", TokenType::NUMBER, "007");
}

TEST(LexerLiterals, NegativeNumberIsTwoTokens) {
    auto tokens = lex_all("-4");
    expect_tokens(tokens, {
        {TokenType::MINUS, "-"},
        {TokenType::NUMBER, "4"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerLiterals, SimpleFloat) {
    expect_single_token("3.14", TokenType::FLOAT, "3.14");
}

TEST(LexerLiterals, FloatManyDigits) {
    expect_single_token("123.456789", TokenType::FLOAT, "123.456789");
}

TEST(LexerLiterals, FloatWithZeroFraction) {
    expect_single_token("10.0", TokenType::FLOAT, "10.0");
}

TEST(LexerLiterals, SimpleString) {
    expect_single_token("\"Hello\"", TokenType::STRING, "Hello");
}

TEST(LexerLiterals, EmptyString) {
    expect_single_token("\"\"", TokenType::STRING, "");
}

TEST(LexerLiterals, StringWithSpacesAndPunctuation) {
    expect_single_token("\"Hello, World!\"", TokenType::STRING, "Hello, World!");
}

TEST(LexerLiterals, StringWithNumbers) {
    expect_single_token("\"abc123\"", TokenType::STRING, "abc123");
}

TEST(LexerLiterals, SimpleChar) {
    expect_single_token("'a'", TokenType::CHAR, "a");
}

TEST(LexerLiterals, DigitChar) {
    expect_single_token("'7'", TokenType::CHAR, "7");
}

TEST(LexerLiterals, SpaceChar) {
    expect_single_token("' '", TokenType::CHAR, " ");
}