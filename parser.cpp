#include "parser.h"

Parser::Parser(const std::string& expr) : infix_str(expr) {
    priority["("] = 0;
    priority[")"] = 0;

    priority["|"] = 1;
    priority["+"] = 1;
    priority["-"] = 1;
    priority["/"] = 1;

    priority["&"] = 2;
    priority["^"] = 2;

    priority["!"] = 3;
    priority["~"] = 3;

    valid_operators = {"|", "+", "-", "/", "&", "^", "!", "~"};
}

Parser::~Parser() {}

void Parser::setPriority(const std::string& op, int prio) {
    priority[op] = prio;
}

void Parser::validate(const std::string& expr) {
    std::stack<char> brackets;
    bool expect_operand = true;
    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];
        if (std::isspace(c)) {
            continue;
        }
        if (std::isalpha(c)) {
            if (!expect_operand) {
                throw std::invalid_argument("Некорректный оператор на позиции " + std::to_string(i));
            }
            expect_operand = false;
            continue;
        }
        if (c == '(') {
            if (!expect_operand) {
                throw std::invalid_argument("Незакрытая скобка на позиции " + std::to_string(i));
            }
            brackets.push(c);
        } else if (c == ')') {
            if (expect_operand) {
                throw std::invalid_argument("Незакрытая скобка на позиции " + std::to_string(i));
            }
            if (brackets.empty() || brackets.top() != '(') {
                throw std::invalid_argument("Незакрытая скобка на позиции " + std::to_string(i));
            }
            brackets.pop();
        } else if (valid_operators.count(std::string(1, c)) > 0) {
            if (c == '!' || c == '~') {
                expect_operand = true;
            } else if (expect_operand) {
                throw std::invalid_argument("Неправильный оператор '" + std::string(1, c) + "' на позиции " + std::to_string(i));
            } else {
                expect_operand = true;
            }
        } else {
            throw std::invalid_argument("Неправильный символ '" + std::string(1, c) + "' на позиции " + std::to_string(i));
        }
    }
    if (expect_operand) {
        throw std::invalid_argument("Незаконченное выражение");
    }

    if (!brackets.empty()) {
        throw std::invalid_argument("Незакрытые скобки.");
    }
}

std::string Parser::to_postfix_form(const std::string& expr) {
    validate(expr);
    std::stack<std::string> operators;
    std::stringstream output;
    int pos = 0;
    while (pos < expr.length()) {
        char c = expr[pos];
        if (std::isspace(c)) {
            pos++;
            continue;
        }
        if (std::isalpha(c)) {
            output << get_func_from_string(expr, pos) << " ";
        } else if (c == '(') {
            operators.push("(");
            pos++;
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != "(") {
                output << operators.top() << " ";
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop();
            }
            pos++;
        } else if (valid_operators.count(std::string(1, c)) > 0) {
            std::string op(1, c);
            if (op == "!" || op == "~") {
                operators.push(op);
            } else {
                while (!operators.empty() && priority[operators.top()] >= priority[op]) {
                    output << operators.top() << " ";
                    operators.pop();
                }
                operators.push(op);
            }
            pos++;
        }
    }
    while (!operators.empty()) {
        output << operators.top() << " ";
        operators.pop();
    }
    return output.str();
}

std::string Parser::get_func_from_string(const std::string& expr, int& pos) {
    std::string str_func = "";
    while (pos < expr.length() && std::isalpha(expr[pos])) {
        str_func += expr[pos];
        pos++;
    }
    if (seen_functions.count(str_func) > 0) {
        throw std::invalid_argument("Повторное использование операнда " + str_func);
    }
    seen_functions.insert(str_func);
    return str_func;
}
