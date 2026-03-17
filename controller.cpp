#include "controller.h"
#include <istream>
#include <ostream>
#include <string>
#include "tokenizer.h"
#include "parser.h"
#include "evaluator.h"

namespace {
    void print_status_error(const char* phase, const Status& status, std::ostream& out) {
        out << "Error: " << phase << ": " << status.message
            << " at " << status.position << "\n";
    }
}

Status run_once(const std::string& line, std::ostream& out) {
    out << "> ";
    if (line == ":help") {
        out << "Mini Expression Evaluator\n";
        out << "Commands:\n";
        out << "  :help  Show this help message\n";
        out << "  :quit  Exit the program\n";
        return make_ok();
    }

    TokenizeResult token_result = tokenize(line);
    if (!is_ok(token_result.status)) {
        print_status_error("tokenizer", token_result.status, out);
        return token_result.status;
    }

    ParseResult parse_result = parse(token_result.tokens);
    if (!is_ok(parse_result.status)) {
        print_status_error("parser", parse_result.status, out);
        return parse_result.status;
    }

    if (!parse_result.root) {
        Status status = make_error("Parser produced empty AST", 0);
        print_status_error("parser", status, out);
        return status;
    }

    EvalResult eval_result = evaluate(*parse_result.root);
    if (!is_ok(eval_result.status)) {
        print_status_error("evaluator", eval_result.status, out);
        return eval_result.status;
    }

    out << "Result: " << eval_result.value << "\n";
    return make_ok();
}

void repl(std::istream& in, std::ostream& out) {
    std::string line;
    while (std::getline(in, line)) {
        if (line == ":quit")
        {
            break;
        }
        run_once(line, out);
        out << "> ";

    }
}
