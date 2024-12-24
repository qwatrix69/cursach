#ifndef DC_H
#define DC_H

#include "../headers.h"

class Dc : public QWidget {
    Q_OBJECT

private:
    int address_inputs;
    int data_outputs;
    std::string oper1;
    std::string oper2;

public:
    explicit Dc(int count_inputs, std::string func, std::string oper1, std::string oper2, QWidget *parent = nullptr);
    std::string func_type;
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MUL_H
