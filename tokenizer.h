#ifndef EXPRESSION_EVALUATOR_TOKENIZER_H
#define EXPRESSION_EVALUATOR_TOKENIZER_H

#include <cstddef>
#include <string>
#include <vector>
// function prototype for tokenizer file
#include "utilities.h"

// for safty and clarity it is better to use class TokenType other than just enum
enum class TokenType {
    Number,
    Plus,
    Minus,
    Star,
    Slash,
    LParen,
    RParen,
    max,
    End
};

struct Token {
    TokenType type;
    long long value;
    std::size_t position;
};

struct TokenizeResult {
    std::vector<Token> tokens;
    Status status;
};

TokenizeResult tokenize(const std::string& expression);


#endif  // EXPRESSION_EVALUATOR_TOKENIZER_H
