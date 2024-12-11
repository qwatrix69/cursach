#include "nand.h"

Nand::Nand(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 100);
}

void Nand::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    QRect rect(10, 10, 180, 80);
    int radius = 40;

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
    p.drawEllipse(QPoint(190, 50), 5, 5);
}
