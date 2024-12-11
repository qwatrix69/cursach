#include "drawer.h"

Drawer::Drawer(QGraphicsScene* scene) : scene(scene) {}

Drawer::~Drawer() {
    clearScene();
}

void Drawer::drawScheme(const std::string& postfixExpr) {
    clearScene();

    int x_offset_operands = 50; // Отступ для операндов (левая часть)
    int y_offset_operands = 50; // Начальная позиция для операндов (вертикально вниз)

    int x_offset_gates = 200; // Отступ для логических элементов (правее операндов)
    int y_offset_gates = 100; // Начальная позиция для логических элементов

    std::vector<QPointF> connection_points;

    for (char c : postfixExpr) {
        if (std::isalpha(c)) {
            // Операнд
            QGraphicsTextItem* operand = new QGraphicsTextItem(QString(c));
            operand->setPos(x_offset_operands, y_offset_operands);
            scene->addItem(operand);
            elements.push_back(operand);

            connection_points.push_back(QPointF(x_offset_operands + 20, y_offset_operands + 10));
            y_offset_operands += 50; // Смещение вниз для следующего операнда
        } else if (c == '^') {
            // AND элемент
            addGate(new And(), connection_points, x_offset_gates, y_offset_gates);
            y_offset_gates += 150; // Смещение вниз для следующего элемента
            x_offset_gates += 100;
        } else if (c == '/') {
            // OR элемент
            addGate(new Or(), connection_points, x_offset_gates, y_offset_gates);
            y_offset_gates += 150;
            x_offset_gates += 100;
        } else if (c == '!') {
            // INVERTOR элемент
            addGate(new Invertor(), connection_points, x_offset_gates, y_offset_gates, 1);
            y_offset_gates += 150;
            x_offset_gates += 100;
        } else if (c == '+') {
            // XOR элемент
            addGate(new Xor(), connection_points, x_offset_gates, y_offset_gates, 1);
            y_offset_gates += 150;
            x_offset_gates += 100;
        }
    }
}

void Drawer::addGate(QWidget* gateWidget, std::vector<QPointF>& connection_points,
                     int x_offset, int y_offset, int inputs) {
    QGraphicsProxyWidget* proxy = scene->addWidget(gateWidget);
    proxy->setPos(x_offset, y_offset);
    elements.push_back(proxy);

    for (int i = 0; i < inputs; ++i) {
        if (connection_points.empty()) break;
        QPointF p = connection_points.back();
        connection_points.pop_back();
        QGraphicsLineItem* line = new QGraphicsLineItem(p.x(), p.y(), x_offset, y_offset + 20 + i * 20);
        scene->addItem(line);
        elements.push_back(line);
    }

    connection_points.push_back(QPointF(x_offset + 100, y_offset + 40));
}


void Drawer::clearScene() {
    for (auto elem : elements) {
        scene->removeItem(elem);
        delete elem;
    }
    elements.clear();
}
