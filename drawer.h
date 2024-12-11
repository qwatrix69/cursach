#ifndef DRAWER_H
#define DRAWER_H

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsLineItem>
#include <vector>
#include "simple_elements/and.h"
#include "simple_elements/or.h"
#include "simple_elements/invertor.h"
#include "simple_elements/xor.h"
#include "simple_elements/buffer.h"
#include "simple_elements/nand.h"
#include "simple_elements/nor.h"
#include "simple_elements/xnor.h"

class Drawer {
public:
    explicit Drawer(QGraphicsScene* scene);

    void drawScheme(const std::string& postfixExpr);

    ~Drawer();

private:
    QGraphicsScene* scene;
    std::vector<QGraphicsItem*> elements;

    void clearScene();
    void addGate(QWidget* gateWidget, std::vector<QPointF>& connection_points,
                 int x_offset, int y_offset, int inputs = 2);
};

#endif // DRAWER_H
