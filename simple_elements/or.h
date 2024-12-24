#ifndef OR_H
#define OR_H

#include "../headers.h"

class Or : public QWidget {
    Q_OBJECT

public:
    explicit Or(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // OR_H
