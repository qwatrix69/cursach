#ifndef PRIORITYWINDOW_H
#define PRIORITYWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>
#include <map>

class PriorityWindow : public QWidget {
    Q_OBJECT // Это необходимо для работы сигналов и слотов

public:
    explicit PriorityWindow(QWidget *parent = nullptr);
    std::map<std::string, int> getPriorities();
    void setPriorities(const std::map<std::string, int>& priorities);

signals:
    void prioritiesChanged(const std::map<std::string, int>& priorities); // Сигнал для передачи приоритетов

private:
    QTableWidget *priorityTable;
    QPushButton *saveButton;
};

#endif // PRIORITYWINDOW_H
