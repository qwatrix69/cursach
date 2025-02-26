#include "priority_window.h"

PriorityWindow::PriorityWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Настройка приоритетов");
    setGeometry(100, 100, 800, 400);
    priorityTable = new QTableWidget(this);
    priorityTable->setColumnCount(3);
    priorityTable->setHorizontalHeaderLabels(QStringList() << "Оператор" << "Приоритет" << "Описание");
    priorityTable->setRowCount(8);
    priorityTable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    priorityTable->horizontalHeader()->setStretchLastSection(true);

    std::map<std::string, int> defaultPriorities = {
        {"|", 1}, {"+", 1}, {"-", 1}, {"/", 1},
        {"&", 2}, {"^", 2}, {"!", 3}, {"~", 3}
    };

    std::map<std::string, QString> descriptions = {
        {"|", "Логическое ИЛИ"},
        {"+", "Исключающее ИЛИ"},
        {"-", "НЕ исключающее ИЛИ"},
        {"/", "НЕ ИЛИ"},
        {"&", "Логическое И"},
        {"^", "НЕ И"},
        {"!", "Логическое НЕ"},
        {"~", "Буфер"}
    };

    int row = 0;
    for (const auto& [op, prio] : defaultPriorities) {
        priorityTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(op)));
        priorityTable->setItem(row, 1, new QTableWidgetItem(QString::number(prio)));
        priorityTable->setItem(row, 2, new QTableWidgetItem(descriptions[op]));
        row++;
    }

    saveButton = new QPushButton("Сохранить", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(priorityTable);
    layout->addWidget(saveButton);
    setLayout(layout);

    connect(saveButton, &QPushButton::clicked, this, [this]() {
        std::map<std::string, int> priorities;
        for (int row = 0; row < priorityTable->rowCount(); ++row) {
            QTableWidgetItem *operatorItem = priorityTable->item(row, 0);
            QTableWidgetItem *priorityItem = priorityTable->item(row, 1);
            if (operatorItem && priorityItem) {
                std::string op = operatorItem->text().toStdString();
                int prio = priorityItem->text().toInt();
                if (!op.empty()) {
                    priorities[op] = prio;
                }
            }
        }
        emit prioritiesChanged(priorities);
        close();
    });
}

std::map<std::string, int> PriorityWindow::getPriorities() {
    std::map<std::string, int> priorities;
    for (int row = 0; row < priorityTable->rowCount(); ++row) {
        QTableWidgetItem *operatorItem = priorityTable->item(row, 0);
        QTableWidgetItem *priorityItem = priorityTable->item(row, 1);
        if (operatorItem && priorityItem) {
            std::string op = operatorItem->text().toStdString();
            int prio = priorityItem->text().toInt();
            if (!op.empty()) {
                priorities[op] = prio;
            }
        }
    }
    return priorities;
}

void PriorityWindow::setPriorities(const std::map<std::string, int>& priorities) {
    int row = 0;
    for (const auto& [op, prio] : priorities) {
        priorityTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(op)));
        priorityTable->setItem(row, 1, new QTableWidgetItem(QString::number(prio)));
        row++;
    }
}
