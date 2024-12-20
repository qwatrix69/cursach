#include "parser.h"
#include "drawer.h"
#include "truth_table_window.h"
#include "priority_window.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QDebug>
#include <QComboBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <vector>
#include <algorithm>
#include "complex_elements/mul.h"
#include "complex_elements/dc.h"
#include "complex_elements/cd.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Главное окно
    QWidget mainWindow;
    mainWindow.setGeometry(200, 200, 1440, 1000);

    // Поле для ввода формулы
    QLineEdit *input_string = new QLineEdit(&mainWindow);
    input_string->setPlaceholderText("Введите формулу");
    input_string->setGeometry(20, 20, 800, 40);

    // Кнопка "Построить"
    QPushButton *go_but = new QPushButton("Построить", &mainWindow);
    go_but->setGeometry(830, 20, 140, 40);

    // Кнопка "Таблица истинности"
    QPushButton *truth_table_but = new QPushButton("Таблица истинности", &mainWindow);
    truth_table_but->setGeometry(980, 20, 140, 40);

    // Кнопка "Задать приоритеты"
    QPushButton *priority_button = new QPushButton("Задать приоритеты", &mainWindow);
    priority_button->setGeometry(1130, 20, 140, 40);

    // Выпадающий список для выбора режима
    QComboBox *elementComboBox = new QComboBox(&mainWindow);
    elementComboBox->addItem("Выбрать режим");
    elementComboBox->addItem("Дешифратор");
    elementComboBox->addItem("Шифратор");
    elementComboBox->addItem("Мультиплексор");
    elementComboBox->addItem("Простые элементы");
    elementComboBox->setGeometry(1280, 20, 140, 40);

    // Графическая сцена и виджет
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(scene, &mainWindow);
    view->setGeometry(20, 80, 1400, 800);
    view->setRenderHint(QPainter::Antialiasing);

    // Отрисовщик схем
    Drawer drawer(scene);

    // Окно для задания приоритетов
    PriorityWindow *priorityWindow = new PriorityWindow();

    // Обработчик кнопки "Задать приоритеты"
    QObject::connect(priority_button, &QPushButton::clicked, [&]() {
        priorityWindow->show();
    });

    // Обработчик кнопки "Построить"
    QObject::connect(go_but, &QPushButton::clicked, [&]() {
        QString inputText = input_string->text();
        if (inputText.isEmpty()) {
            QMessageBox::warning(&mainWindow, "Ошибка", "Введите формулу перед построением!");
            return;
        }

        try {
            std::string input_text = inputText.toStdString();

            Parser *pars = new Parser(input_text);

            // Получаем приоритеты из окна настроек
            std::map<std::string, int> priorities = priorityWindow->getPriorities();

            // Устанавливаем приоритеты
            for (const auto& [op, prio] : priorities) {
                pars->setPriority(op, prio);
            }

            // Преобразуем выражение в постфиксную форму
            std::string postfixExpr = pars->to_postfix_form(input_text);

            QString selectedElement = elementComboBox->currentText();
            if (selectedElement == "Дешифратор") {
                drawer.drawDc(postfixExpr);
            } else if (selectedElement == "Шифратор") {
                drawer.drawCd(postfixExpr);
            } else if (selectedElement == "Мультиплексор") {
                drawer.drawMul(postfixExpr);
            } else if (selectedElement == "Простые элементы") {
                drawer.drawScheme(postfixExpr);
            }

            delete pars; // Удаляем парсер
        } catch (const QString &error) {
            QMessageBox::critical(&mainWindow, "Ошибка", error);
        } catch (const std::exception &ex) {
            QMessageBox::critical(&mainWindow, "Ошибка", ex.what());
        } catch (...) {
            QMessageBox::critical(&mainWindow, "Ошибка", "Произошла неизвестная ошибка.");
        }
    });

    // Обработчик кнопки "Таблица истинности"
    QObject::connect(truth_table_but, &QPushButton::clicked, [&]() {
        QString inputText = input_string->text();
        if (inputText.isEmpty()) {
            QMessageBox::warning(&mainWindow, "Ошибка", "Введите формулу перед построением таблицы истинности!");
            return;
        }

        try {
            std::string input_text = inputText.toStdString();

            Parser *pars = new Parser(input_text);

            // Получаем приоритеты из окна настроек
            std::map<std::string, int> priorities = priorityWindow->getPriorities();

            // Устанавливаем приоритеты
            for (const auto& [op, prio] : priorities) {
                pars->setPriority(op, prio);
            }

            // Преобразуем выражение в постфиксную форму
            std::string postfixExpr = pars->to_postfix_form(input_text);

            // Создаем и отображаем окно с таблицей истинности
            TruthTableWindow *truthTableWindow = new TruthTableWindow();
            truthTableWindow->makeTruthTable(postfixExpr);
            truthTableWindow->show();

            delete pars; // Удаляем парсер
        } catch (const QString &error) {
            QMessageBox::critical(&mainWindow, "Ошибка", error);
        } catch (const std::exception &ex) {
            QMessageBox::critical(&mainWindow, "Ошибка", ex.what());
        } catch (...) {
            QMessageBox::critical(&mainWindow, "Ошибка", "Произошла неизвестная ошибка.");
        }
    });

    mainWindow.show();
    return app.exec();
}
