#include "and.h"
#include <QGraphicsProxyWidget>
#include <QPainter>
#include <QPainterPath>

And::And(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 100);
}

void And::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    QRect rect(10, 10, 180, 90);
    int radius = 40;
    int input1[] = {10, 40};
    int input2[] = {10, 70};
    int output[] = {190, 55};


    QPainterPath path;
    path.moveTo(rect.topLeft());
    path.lineTo(rect.topRight().x() - radius, rect.topRight().y());
    path.arcTo(rect.right() - 2 * radius, rect.top(), 2 * radius, rect.height(), 90, -180);
    path.lineTo(rect.bottomLeft());
    path.closeSubpath();

    p.setBrush(Qt::white);
    p.setPen(QPen(Qt::black, 2));
    p.drawPath(path);

    p.setBrush(Qt::red);
    p.drawEllipse(QPoint(input1[0], input1[1]), 2, 2);
    p.drawEllipse(QPoint(input2[0], input2[1]), 2, 2);
    p.drawEllipse(QPoint(output[0], output[1]), 2, 2);
}

