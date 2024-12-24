#ifndef XNOR_H
#define XNOR_H

#include "../headers.h"

class Xnor : public QWidget {
    Q_OBJECT

public:
    explicit Xnor(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // XNOR_H
