#ifndef DRAWER_H
#define DRAWER_H

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsLineItem>
#include <vector>
#include <stack>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include "simple_elements/and.h"
#include "simple_elements/or.h"
#include "simple_elements/invertor.h"
#include "simple_elements/xor.h"
#include "simple_elements/buffer.h"
#include "simple_elements/nand.h"
#include "simple_elements/nor.h"
#include "simple_elements/xnor.h"
#include "complex_elements/mul.h"
#include "complex_elements/dc.h"
#include "complex_elements/cd.h"

class Drawer {
public:
    explicit Drawer(QGraphicsScene* scene);
    void drawScheme(const std::string& postfixExpr);
    void drawMul(const std::string& postfixExpr);
    void drawDc(const std::string& postfixExpr);
    void drawCd(const std::string& postfixExpr);
    ~Drawer();

private:
    QGraphicsScene* scene;
    std::vector<QGraphicsItem*> elements;
    void clearScene();
    void addGate(QWidget* gateWidget, std::vector<QPointF>& connection_points, int x_offset, int y_offset, int inputs = 2, int flag = 0, int dist = 0, int inv = 0);
    void add_mul(QWidget *gateWidget, std::vector<QPointF> &connection_points, int x_offset, int y_offset, int dist, int inputs);
    void add_dc(QWidget *gateWidget, std::vector<QPointF> &connection_points, int x_offset, int y_offset, int dist, std::string func);
    void add_cd(QWidget *gateWidget, std::vector<QPointF> &connection_points, int x_offset, int y_offset, int dist, std::string func);
    void draw_ellipse(QPoint output);
};

#endif // DRAWER_H
