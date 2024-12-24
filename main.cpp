#include "headers.h"
#include "parser.h"
#include "drawer.h"
#include "priority_window.h"
#include "truth_table_window.h"

#include "simple_elements/and.h"
#include "simple_elements/or.h"
#include "simple_elements/invertor.h"
#include "simple_elements/xor.h"
#include "simple_elements/buffer.h"
#include "simple_elements/nand.h"
#include "simple_elements/nor.h"
#include "simple_elements/xnor.h"

#include "complex_elements/mul.h"
#include "complex_elements/dc.h"
#include "complex_elements/cd.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget mainWindow;
    mainWindow.setGeometry(200, 200, 1440, 1000);

    QLineEdit *input_string = new QLineEdit(&mainWindow);
    input_string->setPlaceholderText("Введите формулу");
    input_string->setGeometry(20, 20, 800, 40);

    QPushButton *go_but = new QPushButton("Построить", &mainWindow);
    go_but->setGeometry(830, 20, 140, 40);

    QPushButton *truth_table_but = new QPushButton("Таблица истинности", &mainWindow);
    truth_table_but->setGeometry(980, 20, 140, 40);

    QPushButton *priority_button = new QPushButton("Задать приоритеты", &mainWindow);
    priority_button->setGeometry(1130, 20, 140, 40);

    QComboBox *elementComboBox = new QComboBox(&mainWindow);
    elementComboBox->addItem("Выбрать режим");
    elementComboBox->addItem("Дешифратор");
    elementComboBox->addItem("Шифратор");
    elementComboBox->addItem("Мультиплексор");
    elementComboBox->addItem("Простые элементы");
    elementComboBox->setGeometry(1280, 20, 140, 40);

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(scene, &mainWindow);
    view->setGeometry(20, 80, 1400, 800);
    view->setRenderHint(QPainter::Antialiasing);

    Drawer drawer(scene);
    PriorityWindow *priorityWindow = new PriorityWindow();
    QObject::connect(priority_button, &QPushButton::clicked, [&]() {
        priorityWindow->show();
    });

    QObject::connect(go_but, &QPushButton::clicked, [&]() {
        QString inputText = input_string->text();
        drawer.clearScene();
        if (inputText.isEmpty()) {
            QMessageBox::warning(&mainWindow, "Ошибка", "Введите формулу перед построением!");
            return;
        }
        try {
            std::string input_text = inputText.toStdString();
            Parser *pars = new Parser(input_text);
            std::map<std::string, int> priorities = priorityWindow->getPriorities();
            for (const auto& [op, prio] : priorities) {
                pars->setPriority(op, prio);
            }
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
            else {
                QMessageBox::warning(&mainWindow, "Ошибка", "Выберите режим");
            }
            delete pars;
        } catch (const QString &error) {
            QMessageBox::critical(&mainWindow, "Ошибка", error);
        } catch (const std::exception &ex) {
            QMessageBox::critical(&mainWindow, "Ошибка", ex.what());
        } catch (...) {
            QMessageBox::critical(&mainWindow, "Ошибка", "Произошла неизвестная ошибка.");
        }
    });

    QObject::connect(truth_table_but, &QPushButton::clicked, [&]() {
        QString inputText = input_string->text();
        if (inputText.isEmpty()) {
            QMessageBox::warning(&mainWindow, "Ошибка", "Введите формулу перед построением таблицы истинности!");
            return;
        }
        try {
            std::string input_text = inputText.toStdString();
            Parser *pars = new Parser(input_text);
            std::map<std::string, int> priorities = priorityWindow->getPriorities();
            for (const auto& [op, prio] : priorities) {
                pars->setPriority(op, prio);
            }
            std::string postfixExpr = pars->to_postfix_form(input_text);
            TruthTableWindow *truthTableWindow = new TruthTableWindow();
            truthTableWindow->makeTruthTable(postfixExpr);
            truthTableWindow->show();
            delete pars;
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
