#include "mul.h"

Mul::Mul(int count_inputs, std::string func, std::string oper1, std::string oper2, QWidget *parent)
    : QWidget(parent), func_type(func), oper1(oper1), oper2(oper2) {
    address_inputs = count_inputs / 2; // Половина входов для адресов
    data_inputs = count_inputs;        // Остальные входы - для данных
    setFixedSize(200, 40 * address_inputs + 25 * data_inputs + 50); // Установка размера окна
}

void Mul::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    int address_section_height = 40; // Высота секции адресного входа
    int data_section_height = 25;    // Высота секции данных
    int start_x = 10, start_y = 10;
    int width = 120; // Ширина секций мультиплексора

    // Общая высота мультиплексора
    int total_height = (address_inputs * address_section_height) +
                       (data_inputs * data_section_height) + 40;

    std::vector<std::string> truth_table;

    if (func_type == "&") {
        truth_table.push_back("0");
        truth_table.push_back("0");
        truth_table.push_back("0");
        truth_table.push_back("1");
    }

    else if (func_type == "|") {
        truth_table.push_back("0");
        truth_table.push_back("1");
        truth_table.push_back("1");
        truth_table.push_back("1");
    }

    else if (func_type == "+") {
        truth_table.push_back("0");
        truth_table.push_back("1");
        truth_table.push_back("1");
        truth_table.push_back("0");
    }

    else if (func_type == "!") {
        truth_table.push_back("1");
        truth_table.push_back("0");
    }

    // Рисуем основную рамку мультиплексора
    QPainterPath path;
    QRect rect(start_x, start_y, width, total_height);
    path.addRect(rect);
    p.setPen(Qt::black);
    p.drawPath(path);

    // Линия входа по центру
    int center_x = start_x - 10; // Сдвиг линии влево на 10

    // Секция адресных входов
    int y_offset = start_y;
    for (int i = address_inputs - 1; i > -1; --i) {
        QRect addr_rect(start_x, y_offset, width / 3, address_section_height);
        p.drawRect(addr_rect);
        p.drawText(addr_rect, Qt::AlignCenter, "A" + QString::number(i));
        y_offset += address_section_height;

        // Линия соединения адреса с центральной линией
        p.drawLine(center_x, y_offset - address_section_height / 2, start_x, y_offset - address_section_height / 2);
        /*QRect name_rect(center_x - 7, y_offset - address_section_height / 2 - 17, 20, 20);
        std::string temp = *funcs.begin(); funcs.erase(funcs.begin());
        p.drawText(name_rect, Qt::AlignCenter, QString::fromStdString(temp)); */

    }

    // Секция данных
    for (int i = data_inputs - 1; i > -1; --i) {
        QRect data_rect(start_x, y_offset, width / 3, data_section_height);
        p.drawRect(data_rect);
        p.drawText(data_rect, Qt::AlignCenter, "D" + QString::number(i));
        y_offset += data_section_height;

        // Линия соединения данных с центральной линией
        p.drawLine(center_x, y_offset - data_section_height / 2, start_x, y_offset - data_section_height / 2);
        QRect name_rect(center_x - 1, y_offset - address_section_height / 2 - 3, 10, 10);
        std::string temp = truth_table.back(); truth_table.pop_back();
        p.drawText(name_rect, Qt::AlignCenter, QString::fromStdString(temp));
    }

    // Секция входа Enable (E)
    QRect e_rect(start_x, y_offset, width / 3, 40);
    p.drawRect(e_rect);
    p.drawText(e_rect, Qt::AlignCenter, "E");

    // Линия соединения E с центральной линией
    p.drawLine(center_x, y_offset + 20, start_x, y_offset + 20);
    QRect name_rect(center_x - 5, y_offset + 4, 20, 20);
    p.drawText(name_rect, Qt::AlignCenter, "1");

    // Средняя секция "MS"
    QRect ms_rect(start_x + (width / 3), start_y, width / 3, total_height);
    p.drawRect(ms_rect);
    p.drawText(ms_rect, Qt::AlignCenter, "MS");

    // Правая секция с результатом
    QRect result_rect(start_x + (2 * width / 3), start_y, width / 3, total_height);
    p.drawRect(result_rect);

    QString result_text;
    // Создаём текст и формат отображения
    if (func_type == "!") {
        result_text = QString::fromStdString(func_type + oper1);
    }
    else {
        result_text = QString::fromStdString(oper1 + " " + func_type + " " + oper2);
    }
    QTextOption text_option;
    text_option.setAlignment(Qt::AlignCenter);      // Центровка текста по горизонтали
    text_option.setWrapMode(QTextOption::WordWrap); // Включение переноса текста

    // Настраиваем шрифт
    QFont font = p.font();
    font.setPointSize(10); // Измените размер шрифта, если текст слишком плотный
    p.setFont(font);

    // Рисуем текст в прямоугольнике с учётом распределения по высоте
    p.drawText(result_rect, result_text, text_option);

}
