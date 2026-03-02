#ifndef EXPRESSION_EVALUATOR_PARSER_H
#define EXPRESSION_EVALUATOR_PARSER_H

#include <vector>

#include "tokenizer.h"
#include "utilities.h"

namespace expr {

struct AstNode {
    int placeholder;
};

struct ParseResult {
    AstNode* root;
    Status status;
};

ParseResult parse(const std::vector<Token>& tokens);

}  // namespace expr

#endif  // EXPRESSION_EVALUATOR_PARSER_H
