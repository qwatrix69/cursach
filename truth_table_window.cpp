#include "truth_table_window.h"

TruthTableWindow::TruthTableWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Таблица истинности");
    setGeometry(100, 100, 1000, 600);
}

void TruthTableWindow::makeTruthTable(const std::string& postfixExpr) {
    std::vector<std::string> variables = get_variables_from_postfix(postfixExpr); // Получаем список переменных из выражения
    int n = variables.size();
    int totalCombinations = 1 << n;
    int operatorsCount = count_operators(postfixExpr);
    int intermediateColumns = operatorsCount;

    QTableWidget *table = new QTableWidget(totalCombinations, n + intermediateColumns );
    QStringList headerLabels;

    for (const std::string& var : variables) {
        headerLabels.append(QString::fromStdString(var));
    }

    for (int i = 0; i < intermediateColumns; ++i) {
        headerLabels.append(QString("Intermediate %1").arg(i + 1)); // Промежуточный результат
    }

    table->setHorizontalHeaderLabels(headerLabels);
    for (int i = 0; i < totalCombinations; ++i) {
        std::map<std::string, bool> values;
        for (int j = 0; j < n; ++j) {
            values[variables[j]] = (i >> (n - j - 1)) & 1;
            table->setItem(i, j, new QTableWidgetItem(values[variables[j]] ? "1" : "0"));
        }

        std::vector<std::string> intermediateResults;
        std::vector<std::string> headers;
        evaluate_with_intermediates(postfixExpr, values, intermediateResults, headers);
        for (int j = 0; j < intermediateColumns; ++j) {
            table->setItem(i, n + j, new QTableWidgetItem(QString::fromStdString(intermediateResults[j])));
        }
        QStringList headerLabels1;

        for (const std::string& var : variables) {
            headerLabels1.append(QString::fromStdString(var));
        }

        for (int i = 0; i < intermediateColumns; ++i) {
            if (!headers.empty()) {
                std::string temp = headers.front();
                headers.erase(headers.begin());
                headerLabels1.append(QString::fromStdString(temp));
            } else {
                headerLabels1.append("Ошибка");
            }
        }
        table->setHorizontalHeaderLabels(headerLabels1);
        bool result = evaluate_postfix(postfixExpr, values);
        table->setItem(i, n + intermediateColumns, new QTableWidgetItem(result ? "1" : "0"));
    }
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(table);
    setLayout(layout);
}

std::vector<std::string> TruthTableWindow::get_variables_from_postfix(const std::string& postfixExpr) {
    std::vector<std::string> variables;
    std::set<std::string> seen;

    for (char c : postfixExpr) {
        if (std::isalpha(c)) {
            std::string var(1, c);
            if (seen.find(var) == seen.end()) {
                variables.push_back(var);
                seen.insert(var);
            }
        }
    }
    return variables;
}


// Метод для подсчета количества операторов в постфиксной записи
int TruthTableWindow::count_operators(const std::string& postfixExpr) {
    int operatorCount = 0;
    for (char c : postfixExpr) {
        if (c == '&' || c == '|' || c == '^' || c == '!' || c == '~' || c == '/' || c == '+' || c == '-') {
            operatorCount++;
        }
    }
    return operatorCount;
}

// Метод для вычисления промежуточных результатов
void TruthTableWindow::evaluate_with_intermediates(const std::string& postfixExpr,
                                                   const std::map<std::string, bool>& variables,
                                                   std::vector<std::string>& intermediateResults,
                                                   std::vector<std::string>& headers) {
    std::stack<bool> stack;
    std::stack<std::string> stack_str; // Стек для хранения промежуточных операций

    for (char c : postfixExpr) {
            std::string oper;
        if (std::isalpha(c)) {
            std::string var(1, c);
            stack_str.push(var);
            stack.push(variables.at(var)); // Значение переменной
        } else if (c == '&') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            std::string b_s = stack_str.top(); stack_str.pop();
            std::string a_s = stack_str.top(); stack_str.pop();
            bool res = a && b; // Логическое И
            std::string res_str = a_s + "&" + b_s;
            stack.push(res);
            stack_str.push(res_str);
            oper += a_s + "&" + b_s;
            intermediateResults.push_back(std::to_string(res));
            headers.push_back(oper);
        } else if (c == '|') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            std::string b_s = stack_str.top(); stack_str.pop();
            std::string a_s = stack_str.top(); stack_str.pop();
            bool res = a || b; // Логическое ИЛИ
            stack.push(res);
            std::string res_str = a_s + "|" + b_s;
            stack_str.push(res_str);
            oper += a_s + "|" + b_s;
            intermediateResults.push_back(std::to_string(res));
            headers.push_back(oper);
        } else if (c == '^') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            std::string b_s = stack_str.top(); stack_str.pop();
            std::string a_s = stack_str.top(); stack_str.pop();
            oper += a_s + "^" + b_s;
            std::string res_str = a_s + "^" + b_s;
            stack_str.push(res_str);
            bool res = a != b; // Логическое исключающее ИЛИ
            stack.push(res);
            intermediateResults.push_back(std::to_string(res));
            headers.push_back(oper);
        } else if (c == '!') {
            bool a = stack.top(); stack.pop();
            std::string a_s = stack_str.top(); stack_str.pop();
            bool res = !a; // Логическое НЕ
            stack.push(res);
            oper += "!" + a_s;
            std::string res_str = "!" + a_s;
            stack_str.push(res_str);
            intermediateResults.push_back(std::to_string(res));
            headers.push_back(oper);
        } else if (c == '~') {
            bool a = stack.top(); stack.pop();
            std::string a_s = stack_str.top(); stack_str.pop();
            stack.push(a); // Буфер (не меняет значение)
            oper += a_s;
            std::string res_str = a_s;
            stack_str.push(res_str);
            intermediateResults.push_back(std::to_string(a));
            headers.push_back(oper);
        } else if (c == '/') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            std::string b_s = stack_str.top(); stack_str.pop();
            std::string a_s = stack_str.top(); stack_str.pop();
            oper += a_s + "/" + b_s;
            bool res = !(a || b); // Логическое НЕ ИЛИ
            stack.push(res);
            std::string res_str = a_s + "/" + b_s;
            stack_str.push(res_str);
            intermediateResults.push_back(std::to_string(res));
            headers.push_back(oper);
        } else if (c == '+') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            std::string b_s = stack_str.top(); stack_str.pop();
            std::string a_s = stack_str.top(); stack_str.pop();
            oper += a_s + "+" + b_s;
            bool res = a != b; // Логическое исключающее ИЛИ
            stack.push(res);
            std::string res_str = a_s + "+" + b_s;
            stack_str.push(res_str);
            intermediateResults.push_back(std::to_string(res));
            headers.push_back(oper);
        } else if (c == '-') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            std::string b_s = stack_str.top(); stack_str.pop();
            std::string a_s = stack_str.top(); stack_str.pop();
            oper += a_s + "-" + b_s;
            bool res = !(a != b); // Логическое НЕ исключающее ИЛИ
            stack.push(res);
            std::string res_str = a_s + "-" + b_s;
            stack_str.push(res_str);
            intermediateResults.push_back(std::to_string(res));
            headers.push_back(oper);
        }
    }
}

// Метод для вычисления результата из постфиксной записи
bool TruthTableWindow::evaluate_postfix(const std::string& postfixExpr, const std::map<std::string, bool>& variables) {
    std::stack<bool> stack;

    for (char c : postfixExpr) {
        if (std::isalpha(c)) {
            std::string var(1, c);
            stack.push(variables.at(var)); // Значение переменной
        } else if (c == '&') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            stack.push(a && b); // Логическое И
        } else if (c == '|') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            stack.push(a || b); // Логическое ИЛИ
        } else if (c == '^') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            stack.push(a != b); // Логическое исключающее ИЛИ
        } else if (c == '!') {
            bool a = stack.top(); stack.pop();
            stack.push(!a); // Логическое НЕ
        } else if (c == '~') {
            bool a = stack.top(); stack.pop();
            stack.push(a); // Буфер (не меняет значение)
        } else if (c == '/') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            stack.push(!(a || b)); // Логическое НЕ ИЛИ
        } else if (c == '+') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            stack.push(a != b); // Логическое исключающее ИЛИ
        } else if (c == '-') {
            bool b = stack.top(); stack.pop();
            bool a = stack.top(); stack.pop();
            stack.push(!(a != b)); // Логическое НЕ исключающее ИЛИ
        }
    }

    return stack.top();
}
