#ifndef MUL_H
#define MUL_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class Mul : public QWidget {
    Q_OBJECT

private:
    int address_inputs; // Количество адресных входов
    int data_inputs;    // Количество входов данных
    std::string func_type;      // Тип функции мультиплексора (например, X + Y или /X)
    std::string oper1;
    std::string oper2;

public:
    explicit Mul(int count_inputs, std::string func, std::string oper1, std::string oper2, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MUL_H
