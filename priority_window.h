#ifndef PRIORITYWINDOW_H
#define PRIORITYWINDOW_H

#include "headers.h"

class PriorityWindow : public QWidget {
    Q_OBJECT

public:
    explicit PriorityWindow(QWidget *parent = nullptr);
    std::map<std::string, int> getPriorities();
    void setPriorities(const std::map<std::string, int>& priorities);

signals:
    void prioritiesChanged(const std::map<std::string, int>& priorities);

private:
    QTableWidget *priorityTable;
    QPushButton *saveButton;
};

#endif // PRIORITYWINDOW_H
