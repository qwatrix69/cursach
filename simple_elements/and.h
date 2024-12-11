#ifndef AND_H
#define AND_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>

class And : public QWidget {
    Q_OBJECT
    int input1[2];
    int input2[2];
    int output[2];

public:
    explicit And(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // AND_H
