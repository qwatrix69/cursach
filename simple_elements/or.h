#ifndef OR_H
#define OR_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class Or : public QWidget {
    Q_OBJECT

public:
    explicit Or(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // OR_H
