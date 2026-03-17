#include "evaluator.h"

namespace {
    EvalResult evaluate_node(const AstNode& node);
    EvalResult evaluate_number(const NumberNode& node);
    EvalResult evaluate_unary(const UnaryNode& node);
    EvalResult evaluate_binary(const BinaryNode& node);
    EvalResult apply_binary(BinaryOperator op, long long left, long long right, std::size_t position);

    EvalResult evaluate_node(const AstNode& node) {
        switch (node.type) {
        case AstNodeType::Number:
            return evaluate_number(static_cast<const NumberNode&>(node));
        case AstNodeType::Unary:
            return evaluate_unary(static_cast<const UnaryNode&>(node));
        case AstNodeType::Binary:
            return evaluate_binary(static_cast<const BinaryNode&>(node));
        default:
            return EvalResult{ 0, make_error("Unknown AST node type", node.position) };
        }
    }

    EvalResult evaluate_number(const NumberNode& node) {
        return EvalResult{ node.value, make_ok() };
    }

    EvalResult evaluate_unary(const UnaryNode& node) {
        if (!node.operand) {
            return EvalResult{ 0, make_error("Unary node missing operand", node.position) };
        }

        EvalResult operand_result = evaluate_node(*node.operand);
        if (!is_ok(operand_result.status)) {
            return operand_result;
        }

        switch (node.op) {
        case UnaryOperator::Negate:
            return EvalResult{ -operand_result.value, make_ok() };
        default:
            return EvalResult{ 0, make_error("Unknown unary operator", node.position) };
        }
    }

    EvalResult evaluate_binary(const BinaryNode& node) {
        if (!node.left || !node.right) {
            return EvalResult{ 0, make_error("Binary node missing operand", node.position) };
        }

        EvalResult left_result = evaluate_node(*node.left);
        if (!is_ok(left_result.status)) {
            return left_result;
        }

        EvalResult right_result = evaluate_node(*node.right);
        if (!is_ok(right_result.status)) {
            return right_result;
        }

        return apply_binary(node.op, left_result.value, right_result.value, node.position);
    }

    EvalResult apply_binary(BinaryOperator op, long long left, long long right, std::size_t position) {
        switch (op) {
        case BinaryOperator::Add:
            return EvalResult{ left + right, make_ok() };
        case BinaryOperator::Subtract:
            return EvalResult{ left - right, make_ok() };
        case BinaryOperator::Multiply:
            return EvalResult{ left * right, make_ok() };
        case BinaryOperator::Divide:
            if (right == 0) {
                return EvalResult{ 0, make_error("Division by zero", position) };
            }
            return EvalResult{ left / right, make_ok() };
        default:
            return EvalResult{ 0, make_error("Unknown binary operator", position) };
        }
    }
}

EvalResult evaluate(const AstNode& root) {
    return evaluate_node(root);
}
