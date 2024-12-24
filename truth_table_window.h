#ifndef TRUTH_TABLE_WINDOW_H
#define TRUTH_TABLE_WINDOW_H

#include "headers.h"

class TruthTableWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TruthTableWindow(QWidget *parent = nullptr);
    void makeTruthTable(const std::string& postfixExpr);

private:
    std::vector<std::string> get_variables_from_postfix(const std::string& postfixExpr);
    int count_operators(const std::string& postfixExpr);
    bool evaluate_postfix(const std::string& postfixExpr, const std::map<std::string, bool>& variables);
    void evaluate_with_intermediates(const std::string& postfixExpr, const std::map<std::string, bool>& variables,
                                     std::vector<std::string>& intermediateResults, std::vector<std::string>& headers);
};

#endif // TRUTH_TABLE_WINDOW_H
