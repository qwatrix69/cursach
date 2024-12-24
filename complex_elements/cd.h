#ifndef CD_H
#define CD_H

#include "../headers.h"

class Cd : public QWidget {
    Q_OBJECT

private:
    int address_inputs;
    int data_outputs;
    std::string func_type;
    std::string oper1;
    std::string oper2;

public:
    explicit Cd(int count_inputs, std::string func, std::string oper1, std::string oper2, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MUL_H
