#include <gtest/gtest.h>

#include "lexer/lexer.hpp"
#include "helpers.hpp"

using namespace dragonfly::lexer;
using namespace dragonfly::lexer::test;

TEST(LexerIdentifiers, SingleLowercaseLetter) {
    expect_single_token("x", TokenType::IDENTIFIER, "x");
}

TEST(LexerIdentifiers, SingleUppercaseLetter) {
    expect_single_token("X", TokenType::IDENTIFIER, "X");
}

TEST(LexerIdentifiers, LowercaseWord) {
    expect_single_token("add", TokenType::IDENTIFIER, "add");
}

TEST(LexerIdentifiers, CapitalisedTypeName) {
    expect_single_token("Dog", TokenType::IDENTIFIER, "Dog");
}

TEST(LexerIdentifiers, MixedCase) {
    expect_single_token("hEllO", TokenType::IDENTIFIER, "hEllO");
}

TEST(LexerIdentifiers, WithUnderscore) {
    expect_single_token("my_var", TokenType::IDENTIFIER, "my_var");
}

TEST(LexerIdentifiers, LeadingUnderscore) {
    expect_single_token("_private", TokenType::IDENTIFIER, "_private");
}

TEST(LexerIdentifiers, SingleUnderscore) {
    expect_single_token("_", TokenType::IDENTIFIER, "_");
}

TEST(LexerIdentifiers, TrailingDigits) {
    expect_single_token("var123", TokenType::IDENTIFIER, "var123");
}

TEST(LexerIdentifiers, DigitsAndUnderscoresMixedIn) {
    expect_single_token("hEllO_210312903_dfsfFJDSIFJ", TokenType::IDENTIFIER, "hEllO_210312903_dfsfFJDSIFJ");
}

TEST(LexerIdentifiers, ScreamingSnakeCaseConstantStyle) {
    expect_single_token("BUFFER_LENGTH", TokenType::IDENTIFIER, "BUFFER_LENGTH");
}

TEST(LexerIdentifiers, LongTypeLikeName) {
    expect_single_token("SomeRandomType123_hahaha", TokenType::IDENTIFIER, "SomeRandomType123_hahaha");
}

TEST(LexerIdentifiers, StopsAtSymbolWithNoSpace) {
    auto tokens = lex_all("x+y");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "x"},
        {TokenType::PLUS, "+"},
        {TokenType::IDENTIFIER, "y"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerIdentifiers, StopsAtDotWithNoSpace) {
    auto tokens = lex_all("point3d.x");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "point3d"},
        {TokenType::DOT, "."},
        {TokenType::IDENTIFIER, "x"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerIdentifiers, NumberPrefixSplitsIntoTwoTokens) {
    auto tokens = lex_all("123abc");
    expect_tokens(tokens, {
        {TokenType::NUMBER, "123"},
        {TokenType::IDENTIFIER, "abc"},
        {TokenType::END_OF_FILE, ""},
    });
}

TEST(LexerIdentifiers, SeparatedByWhitespaceStayDistinct) {
    auto tokens = lex_all("foo bar baz");
    expect_tokens(tokens, {
        {TokenType::IDENTIFIER, "foo"},
        {TokenType::IDENTIFIER, "bar"},
        {TokenType::IDENTIFIER, "baz"},
        {TokenType::END_OF_FILE, ""},
    });
}