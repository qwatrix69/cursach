#include "parser.h"
#include "drawer.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Главное окно
    QWidget mainWindow;
    mainWindow.setGeometry(200, 200, 1200, 800);

    // Поле для ввода формулы и кнопка
    QLineEdit *input_string = new QLineEdit(&mainWindow);
    input_string->setPlaceholderText("Введите формулу");
    input_string->setGeometry(20, 20, 800, 40);

    QPushButton *go_but = new QPushButton("Построить", &mainWindow);
    go_but->setGeometry(840, 20, 120, 40);

    // Сцена для отображения элементов
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(scene, &mainWindow);
    view->setGeometry(20, 80, 1160, 680);
    view->setRenderHint(QPainter::Antialiasing);

    // Создаем отрисовщик
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

        qDebug() << "Формула в обратной польской нотации: " << QString::fromStdString(postfixExpr);

        // Отрисовка схемы
        drawer.drawScheme(postfixExpr);
    });

    mainWindow.show();
    return app.exec();
}
