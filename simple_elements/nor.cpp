#include "nor.h"

Nor::Nor(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 100);
}

void Nor::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    int input1[] = {30, 30};
    int input2[] = {30, 70};
    int output[] = {140, 50};

    QPainterPath path;
    path.moveTo(20, 20);
    path.quadTo(60, 50, 20, 80);
    path.cubicTo(70, 100, 120, 70, 140, 50);
    path.cubicTo(120, 30, 70, 0, 20, 20);

    p.setBrush(Qt::white);
    p.setPen(QPen(Qt::black, 2));
    p.drawPath(path);

    p.setBrush(Qt::red);
    p.drawEllipse(QPoint(input1[0], input1[1]), 2, 2);
    p.drawEllipse(QPoint(input2[0], input2[1]), 2, 2);
    p.setBrush(Qt::white);
    p.drawEllipse(QPoint(output[0], output[1]), 10, 10);
}




