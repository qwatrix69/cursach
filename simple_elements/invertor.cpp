#include "invertor.h"

Invertor::Invertor(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 200);
}

void Invertor::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setPen(Qt::black);

    QPolygon triangle;
    triangle << QPoint(50, 50)
             << QPoint(50, 100)
             << QPoint(100, 75);

    p.setBrush(Qt::cyan);
    p.drawPolygon(triangle);

    p.setBrush(Qt::red);
    p.drawEllipse(QPoint(100, 75), 5, 5);
}
