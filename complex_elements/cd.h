#ifndef CD_H
#define CD_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class Cd : public QWidget {
    Q_OBJECT

private:
    int address_inputs; // Количество адресных входов
    int data_outputs;    // Количество выходов данных
    std::string func_type;      // Тип функции мультиплексора (например, X + Y или /X)
    std::string oper1;
    std::string oper2;

public:
    explicit Cd(int count_inputs, std::string func, std::string oper1, std::string oper2, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MUL_H
