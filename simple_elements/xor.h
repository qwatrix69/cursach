#ifndef XOR_H
#define XOR_H

#include "../headers.h"

class Xor : public QWidget {
    Q_OBJECT

public:
    explicit Xor(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // XOR_H
