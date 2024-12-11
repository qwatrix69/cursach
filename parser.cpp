#include "parser.h"
#include <iostream>
#include <cctype>
#include <stack>
#include <map>
#include <sstream>

Parser::Parser(const std::string& expr) : infix_str(expr) {
    priority["("] = 0;
    priority[")"] = 0;

    priority["/"] = 1; // ИЛИ
    priority["+"] = 1; // ИСКЛ ИЛИ
    priority["↔"] = 1; // НЕ ИСКЛ ИЛИ
    priority["↓"] = 1; // НЕ ИЛИ

    priority["^"] = 2; // И
    priority["|"] = 2; // НЕ И

    priority["!"] = 3; // НЕ
    priority["?"] = 3; // Буф
}

Parser::~Parser() {
}

std::string Parser::to_postfix_form(const std::string& expr) {
    std::stack<std::string> operators;
    std::stringstream output;
    int pos = 0;

    while (pos < expr.length()) {
        char c = expr[pos];

        if (isalpha(c)) {
            output << get_func_from_string(expr, pos) << " ";
        } else if (c == '(') {
            // Открывающая скобка, добавляем в стек
            operators.push("(");
            pos++;
        } else if (c == ')') {
            // Закрывающая скобка, вытаскиваем операторы из стека до открывающей скобки
            while (!operators.empty() && operators.top() != "(") {
                output << operators.top() << " ";
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop();  // Убираем открытую скобку
            }
            pos++;
        } else if (priority.find(std::string(1, c)) != priority.end()) {
            // Если оператор
            std::string op(1, c);
            while (!operators.empty() && priority[operators.top()] >= priority[op]) {
                output << operators.top() << " ";
                operators.pop();
            }
            operators.push(op);
            pos++;
        } else {
            pos++; // Игнорируем другие символы
        }
    }

    // Добавляем оставшиеся операторы из стека в выходную строку
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
