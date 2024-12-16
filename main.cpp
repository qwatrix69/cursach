#include "parser.h"
#include "drawer.h"
#include "truth_table_window.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QDebug>
#include <QCheckBox>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget mainWindow;
    mainWindow.setGeometry(200, 200, 1400, 1000);

    QLineEdit *input_string = new QLineEdit(&mainWindow);
    input_string->setPlaceholderText("Введите формулу");
    input_string->setGeometry(20, 20, 800, 40);

    QPushButton *go_but = new QPushButton("Построить", &mainWindow);
    go_but->setGeometry(840, 20, 120, 40);

    QPushButton *truth_table_but = new QPushButton("Таблица истинности", &mainWindow);
    truth_table_but->setGeometry(980, 20, 160, 40);

    QCheckBox *complexElementsCheckBox = new QCheckBox("Сложные элементы", &mainWindow);
    complexElementsCheckBox->setGeometry(1160, 20, 200, 40);

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(scene, &mainWindow);
    view->setGeometry(20, 80, 1200, 800);
    view->setRenderHint(QPainter::Antialiasing);

    Drawer drawer(scene);

    QObject::connect(go_but, &QPushButton::clicked, [&]() {
        QString inputText = input_string->text();
        std::string input_text = inputText.toStdString();
        Parser *pars = new Parser(input_text);

        std::string postfixExpr = pars->to_postfix_form(input_text);
        if (postfixExpr.empty()) {
            qDebug() << "Ошибка при преобразовании в постфиксную запись!";
            return;
        }

        if (complexElementsCheckBox->isChecked()) {
            //drawer.drawHardScheme(postfixExpr);
        } else {
            drawer.drawScheme(postfixExpr);
        }
    });

    QObject::connect(truth_table_but, &QPushButton::clicked, [&]() {
        QString inputText = input_string->text();
        std::string input_text = inputText.toStdString();
        Parser *pars = new Parser(input_text);

        std::string postfixExpr = pars->to_postfix_form(input_text);
        if (postfixExpr.empty()) {
            qDebug() << "Ошибка при преобразовании в постфиксную запись!";
            return;
        }

        // Создаем и отображаем окно с таблицей истинности
        TruthTableWindow *truthTableWindow = new TruthTableWindow();
        truthTableWindow->makeTruthTable(postfixExpr);
        truthTableWindow->show();
    });

    mainWindow.show();
    return app.exec();
}
