#include "parser.h"
#include <iostream>
#include <cctype>
#include <stack>
#include <map>
#include <sstream>
#include <stdexcept>
#include <set>

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
    bool expect_operand = true; // Начинаем с ожидания операнда или унарного оператора

    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];

        if (std::isspace(c)) {
            continue; // Пропускаем пробелы
        }

        if (std::isalpha(c)) {
            if (!expect_operand) {
                throw std::invalid_argument("Unexpected operand at position " + std::to_string(i));
            }
            expect_operand = false; // После операнда ожидается оператор
            continue;
        }

        if (c == '(') {
            if (!expect_operand) {
                throw std::invalid_argument("Unexpected opening parenthesis at position " + std::to_string(i));
            }
            brackets.push(c);
        } else if (c == ')') {
            if (expect_operand) {
                throw std::invalid_argument("Unexpected closing parenthesis at position " + std::to_string(i));
            }
            if (brackets.empty() || brackets.top() != '(') {
                throw std::invalid_argument("Unmatched closing parenthesis at position " + std::to_string(i));
            }
            brackets.pop();
        } else if (valid_operators.count(std::string(1, c)) > 0) {
            if (c == '!' || c == '~') {
                expect_operand = true; // Унарные операторы допускаются перед операндом
            } else if (expect_operand) {
                throw std::invalid_argument("Unexpected operator '" + std::string(1, c) + "' at position " + std::to_string(i));
            } else {
                expect_operand = true; // После бинарного оператора ожидается операнд
            }
        } else {
            throw std::invalid_argument("Invalid character '" + std::string(1, c) + "' at position " + std::to_string(i));
        }
    }

    if (expect_operand) {
        throw std::invalid_argument("Expression ends unexpectedly.");
    }

    if (!brackets.empty()) {
        throw std::invalid_argument("Unmatched opening parenthesis.");
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

            // Обрабатываем унарные операторы
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
    return str_func;
}
