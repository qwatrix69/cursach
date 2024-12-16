#include "drawer.h"

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QDebug>

Drawer::Drawer(QGraphicsScene* scene) : scene(scene) {}

Drawer::~Drawer() {
    clearScene();
}

void Drawer::drawScheme(const std::string& postfixExpr) {
    clearScene();

    int x_offset_operands = 50;
    int y_offset_operands = 50;

    int x_offset_gates = 100;
    int dist = 20;

    std::vector<QPointF> connection_points;

    for (char c : postfixExpr) {
        if (std::isalpha(c)) {
            QGraphicsTextItem* operand = new QGraphicsTextItem(QString(c));
            operand->setPos(x_offset_operands, y_offset_operands);
            scene->addItem(operand);
            elements.push_back(operand);
            connection_points.push_back(QPointF(x_offset_operands, y_offset_operands));
            y_offset_operands += 150;
        } else if (c == '&') {
            QPointF temp = connection_points[connection_points.size() - 2];
            addGate(new And(), connection_points, x_offset_gates, temp.y(), 2, 0, dist, 0);
            x_offset_gates += 250;
            dist += 10;
        } else if (c == '^') {
            QPointF temp = connection_points[connection_points.size() - 2];
            addGate(new Nand(), connection_points, x_offset_gates, temp.y(), 2, 0, dist, 1);
            x_offset_gates += 250;
            dist += 10;
        } else if (c == '|') {
            QPointF temp = connection_points[connection_points.size() - 2];
            addGate(new Or(), connection_points, x_offset_gates, temp.y(), 2, 1, dist, 0);
            x_offset_gates += 250;
            dist += 10;
        } else if (c == '!') {
            QPointF temp = connection_points.back();
            addGate(new Invertor(), connection_points, x_offset_gates, temp.y(), 1, 0, dist, 1);
            x_offset_gates += 250;
            dist += 10;
        } else if (c == '~') {
            QPointF temp = connection_points.back();
            addGate(new Buffer(), connection_points, x_offset_gates, temp.y(), 1, 0, dist, 0);
            x_offset_gates += 250;
            dist += 10;
        } else if (c == '/') {
            QPointF temp = connection_points[connection_points.size() - 2];
            addGate(new Nor(), connection_points, x_offset_gates, temp.y(), 2, 1, dist, 1);
            x_offset_gates += 250;
            dist += 10;
        } else if (c == '+') {
            QPointF temp = connection_points[connection_points.size() - 2];
            addGate(new Xor(), connection_points, x_offset_gates, temp.y(), 2, 2, dist, 0);
            x_offset_gates += 250;
            dist += 10;
        } else if (c == '-') {
            QPointF temp = connection_points[connection_points.size() - 2];
            addGate(new Xnor(), connection_points, x_offset_gates, temp.y(), 2, 2, dist, 1);
            x_offset_gates += 250;
            dist += 10;
        }
    }
}

void Drawer::addGate(QWidget *gateWidget, std::vector<QPointF> &connection_points, int x_offset, int y_offset, int inputs, int flag, int dist, int inv) {
    QGraphicsProxyWidget* proxy = scene->addWidget(gateWidget);
    proxy->setPos(x_offset, y_offset);
    elements.push_back(proxy);
    gateWidget->setStyleSheet("background-color: transparent;");

    while (true) {
        QPoint input1;
        QPoint input2;
        QPoint output;
        int add = 0;

        if (inv == 1) {
            add = 4;
        }

        if (inputs == 2 and flag == 0) {
            input1 = QPoint(x_offset + 10, y_offset + 40);
            input2 = QPoint(x_offset + 10, y_offset + 70);
            output = QPoint(x_offset + 190 + add, y_offset + 55);
        }

        else if (inputs == 2 and flag == 1) {
            input1 = QPoint(x_offset + 30, y_offset + 30);
            input2 = QPoint(x_offset + 30, y_offset + 70);
            output = QPoint(x_offset + 140 + add, y_offset + 50);
        }

        else if (inputs == 2 and flag == 2) {
            input1 = QPoint(x_offset + 25, y_offset + 30);
            input2 = QPoint(x_offset + 25, y_offset + 70);
            output = QPoint(x_offset + 140 + add, y_offset + 50);
        }

        else if (inputs == 1) {
            QPoint input1 = QPoint(x_offset + 10, y_offset + 55);
            QPoint output = QPoint(x_offset + 190 + add, y_offset + 55);
            QPointF p1 = connection_points[connection_points.size() - 1];
            connection_points.pop_back();
            QPoint line_part_x_1 = QPoint(p1.x() + dist, p1.y());
            int delta_y = p1.y() - input1.y();
            QPoint line_part_x_2;
            if (delta_y <= 0) {
                line_part_x_2 = QPoint(p1.x() + dist, p1.y() + (-1 * delta_y));
            }
            else {
                line_part_x_2 = QPoint(p1.x() + dist, p1.y() + delta_y);
            }

            QGraphicsLineItem* line_x_1 = new QGraphicsLineItem(p1.x(), p1.y(), line_part_x_1.x(), line_part_x_1.y());
            QGraphicsLineItem* line_x_2 = new QGraphicsLineItem(line_part_x_1.x(), line_part_x_1.y(), line_part_x_2.x(), line_part_x_2.y());
            QGraphicsLineItem* line_x_3 = new QGraphicsLineItem(line_part_x_2.x(), line_part_x_2.y(), input1.x(), input1.y());

            scene->addItem(line_x_1);
            elements.push_back(line_x_1);
            scene->addItem(line_x_2);
            elements.push_back(line_x_2);
            scene->addItem(line_x_3);
            elements.push_back(line_x_3);
            connection_points.push_back(output);
            break;
        }

        QPointF p2 = connection_points.back();
        connection_points.pop_back();
        QPointF p1 = connection_points.back();
        connection_points.pop_back();

        QPoint line_part_x_1 = QPoint(p1.x() + dist, p1.y());
        int delta_y = p1.y() - input1.y();
        QPoint line_part_x_2;
        if (delta_y <= 0) {
            line_part_x_2 = QPoint(p1.x() + dist, p1.y() + (-1 * delta_y));
        }
        else {
            line_part_x_2 = QPoint(p1.x() + dist, p1.y() + delta_y);
        }

        QGraphicsLineItem* line_x_1 = new QGraphicsLineItem(p1.x(), p1.y(), line_part_x_1.x(), line_part_x_1.y());
        QGraphicsLineItem* line_x_2 = new QGraphicsLineItem(line_part_x_1.x(), line_part_x_1.y(), line_part_x_2.x(), line_part_x_2.y());
        QGraphicsLineItem* line_x_3 = new QGraphicsLineItem(line_part_x_2.x(), line_part_x_2.y(), input1.x(), input1.y());

        scene->addItem(line_x_1);
        elements.push_back(line_x_1);
        scene->addItem(line_x_2);
        elements.push_back(line_x_2);
        scene->addItem(line_x_3);
        elements.push_back(line_x_3);

        QPoint line_part_y_1 = QPoint(p2.x() + dist, p2.y());
        int delta_y2 = p2.y() - input2.y();
        QPoint line_part_y_2;
        if (delta_y <= 0) {
            line_part_y_2 = QPoint(p2.x() + dist, p2.y() + (-1 * delta_y2));
        }
        else {
            line_part_y_2 = QPoint(p2.x() + dist, p2.y() + delta_y2);
        }

        QGraphicsLineItem* line2_x_1 = new QGraphicsLineItem(p2.x(), p2.y(), line_part_y_1.x(), line_part_y_1.y());
        QGraphicsLineItem* line2_x_2 = new QGraphicsLineItem(line_part_y_1.x(), line_part_y_1.y(), line_part_y_2.x(), line_part_y_2.y());
        QGraphicsLineItem* line2_x_3 = new QGraphicsLineItem(line_part_y_2.x(), line_part_y_2.y(), input2.x(), input2.y());

        scene->addItem(line2_x_1);
        elements.push_back(line2_x_1);
        scene->addItem(line2_x_2);
        elements.push_back(line2_x_2);
        scene->addItem(line2_x_3);
        elements.push_back(line2_x_3);

        connection_points.push_back(output);
        break;

    }


}


void Drawer::clearScene() {
    for (auto elem : elements) {
        scene->removeItem(elem);
        delete elem;
    }
    elements.clear();
}
