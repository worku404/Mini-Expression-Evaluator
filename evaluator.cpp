#include "evaluator.h"

namespace expr {

EvalResult evaluate(const AstNode& root) {
    (void)root;
    return {0, make_error("Evaluator not implemented yet in Stage 1", 0)};
}

}  // namespace expr
