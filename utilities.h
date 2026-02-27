#ifndef EXPRESSION_EVALUATOR_UTILITIES_H
#define EXPRESSION_EVALUATOR_UTILITIES_H

#include <cstddef>
#include <string>

namespace expr {

struct Status {
    bool ok;
    std::string message;
    std::size_t position;
};

Status make_ok();
Status make_error(const std::string& message, std::size_t position = 0);

inline bool is_ok(const Status& status) {
    return status.ok;
}

}  // namespace expr

#endif  // EXPRESSION_EVALUATOR_UTILITIES_H
