#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <map>

class Parser {
private:
    std::string infix_str;
    std::map<std::string, int> priority;

public:
    Parser(const std::string& expr);
    ~Parser();

    std::string to_postfix_form(const std::string& expr);
    std::string get_func_from_string(const std::string& expr, int& pos);
    bool evaluate_postfix(const std::string& postfix, const std::map<char, bool>& values);
    std::vector<bool> evaluate_with_steps(const std::string& postfixExpr,
                                                  const std::map<char, bool>& values,
                                                  std::vector<std::string>& intermediateSteps);
};

#endif // PARSER_H
