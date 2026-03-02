#include "parser.h"

namespace expr {

ParseResult parse(const std::vector<Token>& tokens) {
    (void)tokens;
    return {nullptr, make_error("Parser not implemented yet in Stage 1", 0)};
}

}  // namespace expr
