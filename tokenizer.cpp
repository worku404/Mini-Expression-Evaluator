#include "tokenizer.h"

namespace expr {

TokenizeResult tokenize(const std::string& expression) {
    (void)expression;
    return {{}, make_error("Tokenizer not implemented yet in Stage 1", 0)};
}

}  // namespace expr
