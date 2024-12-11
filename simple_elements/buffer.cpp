#include "buffer.h"

Buffer::Buffer(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 200);
}

void Buffer::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setPen(Qt::black);

    QPolygon triangle;
    triangle << QPoint(50, 50)
             << QPoint(50, 100)
             << QPoint(100, 75);

    p.setBrush(Qt::cyan);
    p.drawPolygon(triangle);
}
