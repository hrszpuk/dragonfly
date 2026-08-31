#pragma once

// Shared helpers for lexer tests. Include this from any tests/lexer/*.cpp
// file that needs to run the lexer and check its token output.
//
// Lives alongside the test .cpp files (not under lib/) since it's test-only
// scaffolding, not part of the compiler itself.

#include <gtest/gtest.h>

#include <cstddef>
#include <initializer_list>
#include <string>
#include <string_view>
#include <vector>

#include "lexer/lexer.hpp"

namespace dragonfly::lexer::test {

inline std::vector<Token> lex_all(std::string_view source) {
    std::vector<Token> tokens;
    Lexer lexer(source, tokens);
    lexer.lex();
    return tokens;
}

struct Expected {
    TokenType type;
    std::string_view value;
};

// Asserts `tokens` matches `expected` exactly, type and lexeme, in order 
inline void expect_tokens(const std::vector<Token>& tokens, std::initializer_list<Expected> expected) {
    ASSERT_EQ(tokens.size(), expected.size())
        << "token count mismatch — did the lexer over/under-produce tokens?";

    std::size_t i = 0;
    for (const auto& e : expected) {
        SCOPED_TRACE("token index " + std::to_string(i));
        EXPECT_EQ(tokens[i].type, e.type);
        EXPECT_EQ(tokens[i].value, e.value);
        ++i;
    }
}

// Really common pattern in symbols so this reduced duplicate code
inline void expect_single_token(std::string_view source, TokenType type, std::string_view value) {
    auto tokens = lex_all(source);
    expect_tokens(tokens, {
        {type, value},
        {TokenType::END_OF_FILE, ""},
    });
}

}  