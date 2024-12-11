#ifndef NAND_H
#define NAND_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class Nand : public QWidget {
    Q_OBJECT

public:
    explicit Nand(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // NAND_H
