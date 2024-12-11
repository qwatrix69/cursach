#include "xor.h"

Xor::Xor(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 100);
}

void Xor::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    QPainterPath path;

    // Начало пути (нижняя левая часть)
    path.moveTo(20, 20);

    // Левая изогнутая часть
    path.quadTo(60, 50, 20, 80);

    // Правая плавная дуга, сходящаяся в одной точке
    path.cubicTo(70, 100, 120, 70, 140, 50); // Правая верхняя дуга
    path.cubicTo(120, 30, 70, 0, 20, 20);   // Правая нижняя дуга

    // Вторая линия внутри (для XOR)
    QPainterPath path2;
    path2.moveTo(15, 20);   // Начальная точка второй линии
    path2.quadTo(55, 50, 15, 80);    // Конечная точка второй линии

    // Устанавливаем заливку и обводку
    p.setPen(QPen(Qt::black, 2)); // Толщина линии 2
    p.drawPath(path2); // Вторая линия
    p.setBrush(Qt::cyan);
    p.drawPath(path);  // Основной путь OR
}
