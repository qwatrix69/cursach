#ifndef NOR_H
#define NOR_H

#include "../headers.h"

class Nor : public QWidget {
    Q_OBJECT

public:
    explicit Nor(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // NOR_H
