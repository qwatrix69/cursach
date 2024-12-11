#ifndef INVERTOR_H
#define INVERTOR_H

#include <QWidget>
#include <QPainter>

class Invertor : public QWidget {
    Q_OBJECT

public:
    explicit Invertor(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // INVERTOR_H
