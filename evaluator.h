#ifndef EXPRESSION_EVALUATOR_EVALUATOR_H
#define EXPRESSION_EVALUATOR_EVALUATOR_H

#include "parser.h"
#include "utilities.h"

namespace expr {

struct EvalResult {
    long long value;
    Status status;
};

EvalResult evaluate(const AstNode& root);

}  // namespace expr

#endif  // EXPRESSION_EVALUATOR_EVALUATOR_H
