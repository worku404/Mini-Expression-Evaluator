#include "tokenizer.h"

#include <cctype>
#include <limits>

namespace expr {

namespace {

bool is_space(char ch) {
    return std::isspace(static_cast<unsigned char>(ch)) != 0;
}

bool is_digit(char ch) {
    return std::isdigit(static_cast<unsigned char>(ch)) != 0;
}

void skip_whitespace(const std::string& expression, std::size_t& index) {
    while (index < expression.size() && is_space(expression[index])) {
        ++index;
    }
}

Status scan_number(const std::string& expression, std::size_t& index, std::vector<Token>& tokens) {
    const std::size_t start = index;
    // accumulate
    long long value = 0;

    while (index < expression.size() && is_digit(expression[index])) {
        const int digit = expression[index] - '0';
        const long long max_before_mul = std::numeric_limits<long long>::max() / 10;
        const long long max_last_digit = std::numeric_limits<long long>::max() % 10;

        if (value > max_before_mul || (value == max_before_mul && digit > max_last_digit)) {
            return make_error("Integer literal overflow", start);
        }

        value = value * 10 + digit;
        ++index;
    }

    tokens.push_back({TokenType::Number, value, start});
    return make_ok();
}

}  // namespace

TokenizeResult tokenize(const std::string& expression) {
    TokenizeResult result;
    result.status = make_ok();

    std::size_t index = 0;
    while (index < expression.size()) {
        skip_whitespace(expression, index);
        if (index >= expression.size()) {
            break;
        }

        const char current = expression[index];
        if (is_digit(current)) {
            result.status = scan_number(expression, index, result.tokens);
            if (!is_ok(result.status)) {
                return result;
            }
            continue;
        }

        switch (current) {
            case '+':
                result.tokens.push_back({TokenType::Plus, 0, index});
                ++index;
                break;
            case '-':
                result.tokens.push_back({TokenType::Minus, 0, index});
                ++index;
                break;
            case '*':
                result.tokens.push_back({TokenType::Star, 0, index});
                ++index;
                break;
            case '/':
                result.tokens.push_back({TokenType::Slash, 0, index});
                ++index;
                break;
            case '(':
                result.tokens.push_back({TokenType::LParen, 0, index});
                ++index;
                break;
            case ')':
                result.tokens.push_back({TokenType::RParen, 0, index});
                ++index;
                break;
            default:
                result.status = make_error("Invalid character in expression", index);
                return result;
        }
    }

    result.tokens.push_back({TokenType::End, 0, expression.size()});
    return result;
}

}  // namespace expr
