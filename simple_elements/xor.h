#ifndef XOR_H
#define XOR_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class Xor : public QWidget {
    Q_OBJECT

public:
    explicit Xor(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // XOR_H
