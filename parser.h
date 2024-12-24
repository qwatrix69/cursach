#ifndef PARSER_H
#define PARSER_H

#include "headers.h"
#include "parser.h"
#include "drawer.h"
#include "priority_window.h"
#include "truth_table_window.h"

#include "simple_elements/and.h"
#include "simple_elements/or.h"
#include "simple_elements/invertor.h"
#include "simple_elements/xor.h"
#include "simple_elements/buffer.h"
#include "simple_elements/nand.h"
#include "simple_elements/nor.h"
#include "simple_elements/xnor.h"

#include "complex_elements/mul.h"
#include "complex_elements/dc.h"
#include "complex_elements/cd.h"

class Parser {
private:
    std::string infix_str;
    std::map<std::string, int> priority;
    std::set<std::string> valid_operators;
    std::unordered_set<std::string> seen_functions;

public:
    Parser(const std::string& expr);
    ~Parser();

    std::string to_postfix_form(const std::string& expr);
    std::string get_func_from_string(const std::string& expr, int& pos);
    void setPriority(const std::string& op, int prio);
    void validate(const std::string& expr);
};

#endif // PARSER_H
