#include "invertor.h"

Invertor::Invertor(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 100);
}

void Invertor::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::black);

    QRect rect(10, 10, 180, 90);

    QPolygon triangle;
    triangle << QPoint(rect.left(), rect.top())
             << QPoint(rect.left(), rect.bottom())
             << QPoint(rect.right(), rect.center().y());

    p.setBrush(Qt::white);
    p.setPen(QPen(Qt::black, 2));
    p.drawPolygon(triangle);

    p.setBrush(Qt::red);
    p.drawEllipse(QPoint(rect.left(), rect.center().y()), 2, 2);
    p.setBrush(Qt::white);
    p.drawEllipse(QPoint(rect.right(), rect.center().y()), 10, 10);
}

