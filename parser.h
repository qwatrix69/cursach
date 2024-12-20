#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <map>
#include <set>

class Parser {
private:
    std::string infix_str;
    std::map<std::string, int> priority;
    std::set<std::string> valid_operators;

public:
    Parser(const std::string& expr);
    ~Parser();

    std::string to_postfix_form(const std::string& expr);
    std::string get_func_from_string(const std::string& expr, int& pos);
    bool evaluate_postfix(const std::string& postfix, const std::map<char, bool>& values);
    void setPriority(const std::string& op, int prio);
    void validate(const std::string& expr);
};

#endif // PARSER_H
