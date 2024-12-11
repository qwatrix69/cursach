#include "and.h"

And::And(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 100);
}

void And::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    QRect rect(10, 10, 180, 90);
    int radius = 40;
    input1[0] = 40;
    input1[1] = 10;
    input2[0] = 70;
    input2[1] = 10;
    output[0] = 55;
    output[1] = 190;

    QPainterPath path;
    path.moveTo(rect.topLeft());
    path.lineTo(rect.topRight().x() - radius, rect.topRight().y());
    path.arcTo(rect.right() - 2 * radius, rect.top(), 2 * radius, rect.height(), 90, -180);
    path.lineTo(rect.bottomLeft());
    path.closeSubpath();

    p.setBrush(Qt::cyan);
    p.setPen(Qt::black);
    p.drawPath(path);

    p.setBrush(Qt::red);
    p.drawEllipse(QPoint(input1[0], input1[1]), 1, 1);
    p.drawEllipse(QPoint(input2[0], input2[1]), 1, 1);
    p.drawEllipse(QPoint(output[0], output[1]), 1, 1);
}
