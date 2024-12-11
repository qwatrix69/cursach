#ifndef BUFFER_H
#define BUFFER_H

#include <QWidget>
#include <QPainter>

class Buffer : public QWidget {
    Q_OBJECT

public:
    explicit Buffer(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // BUFFER_H