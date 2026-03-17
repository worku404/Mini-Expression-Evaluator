#ifndef EXPRESSION_EVALUATOR_EVALUATOR_H
#define EXPRESSION_EVALUATOR_EVALUATOR_H

#include "parser.h"
#include "utilities.h"


struct EvalResult {
    long long value;
    Status status;
};

EvalResult evaluate(const AstNode& root);


#endif  // EXPRESSION_EVALUATOR_EVALUATOR_H
