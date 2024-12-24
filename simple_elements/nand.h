#ifndef NAND_H
#define NAND_H

#include "../headers.h"

class Nand : public QWidget {
    Q_OBJECT

public:
    explicit Nand(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // NAND_H
