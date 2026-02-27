#ifndef EXPRESSION_EVALUATOR_CONTROLLER_H
#define EXPRESSION_EVALUATOR_CONTROLLER_H

#include <iostream>
#include <string>

#include "utilities.h"

namespace expr {

Status run_once(const std::string& line, std::ostream& out);

void repl(std::istream& in, std::ostream& out);

}  // namespace expr

#endif  // EXPRESSION_EVALUATOR_CONTROLLER_H
