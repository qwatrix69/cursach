#ifndef AND_H
#define AND_H

#include "../headers.h"

class And : public QWidget {
    Q_OBJECT

public:
    explicit And(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // AND_H
