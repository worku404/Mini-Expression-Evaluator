#include "controller.h"

#include <string>

namespace expr {

Status run_once(const std::string& line, std::ostream& out) {
    if (line.empty()) {
        return make_ok();
    }

    if (line == ":help") {
        out << "Mini Expression Evaluator (Stage 1)\n";
        out << "Commands:\n";
        out << "  :help  Show this help message\n";
        out << "  :quit  Exit the program\n";
        out << "Any other input returns a Stage 1 not-implemented status.\n";
        return make_ok();
    }

    return make_error("Not implemented yet in Stage 1", 0);
}

void repl(std::istream& in, std::ostream& out) {
    std::string line;
    while (true) {
        out << "> ";
        if (!std::getline(in, line)) {
            break;
        }
        if (line == ":quit") {
            break;
        }

        const Status status = run_once(line, out);
        if (!is_ok(status)) {
            out << "error: " << status.message;
            if (status.position != 0) {
                out << " (position " << status.position << ')';
            }
            out << '\n';
        }
    }
}

}  // namespace expr
