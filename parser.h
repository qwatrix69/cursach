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
};

#endif // PARSER_H
