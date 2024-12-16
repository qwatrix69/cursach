#include "xor.h"

Xor::Xor(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 100);
}

void Xor::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    QPainterPath path;
    path.moveTo(20, 20);
    path.quadTo(60, 50, 20, 80);

    path.cubicTo(70, 100, 120, 70, 140, 50);
    path.cubicTo(120, 30, 70, 0, 20, 20);

    QPainterPath path2;
    path2.moveTo(15, 22);
    path2.quadTo(55, 50, 15, 78);

    p.setPen(QPen(Qt::black, 2));
    p.drawPath(path2);
    p.setBrush(Qt::white);
    p.drawPath(path);

    QPoint input1(25, 30);
    QPoint input2(25, 70);
    QPoint output(140, 50);

    p.setBrush(Qt::red);
    p.drawEllipse(input1, 2, 2);
    p.drawEllipse(input2, 2, 2);
    p.drawEllipse(output, 2, 2);
}
