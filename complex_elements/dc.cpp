#include "dc.h"

Dc::Dc(int count_inputs, std::string func, std::string oper1, std::string oper2, QWidget *parent)
    : QWidget(parent), func_type(func), oper1(oper1), oper2(oper2) {
    address_inputs = count_inputs; // Половина входов для адресов
    data_outputs = count_inputs * 2;        // Остальные входы - для данных
    setFixedSize(200, 40 * address_inputs + 25 * data_outputs + 50 + 10); // Установка размера окна
}

void Dc::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    int address_section_height = 40; // Высота секции адресного входа
    int data_section_height = ((address_inputs + 1) * 40) / data_outputs;
    int start_x = 10, start_y = 10;
    int width = 120;          // Ширина всего шифратора

    // Общая высота шифратора
    int total_height = data_outputs * data_section_height;

    // Рисуем основную рамку шифратора
    QPainterPath path;
    QRect rect(start_x, start_y, width, total_height);
    path.addRect(rect);
    p.setPen(Qt::black);
    p.drawPath(path);

    int center_x = start_x - 10; // Сдвиг линии влево на 10

    // Центр соединения линий слева и справа
    int center_x_left = start_x - 10;   // Слева
    int center_x_right = start_x + width + 10; // Справа

    // Рисуем входы слева (1, 2, C)
    int y_offset = start_y;
    for (int i = 1; i < address_inputs + 1; ++i) {
        QRect addr_rect(start_x, y_offset, width / 3, address_section_height);
        p.drawRect(addr_rect);
        p.drawText(addr_rect, Qt::AlignCenter, QString::number(i));
        y_offset += address_section_height;

        // Линия соединения адреса с центральной линией
        p.drawLine(center_x, y_offset - address_section_height / 2, start_x, y_offset - address_section_height / 2);
        /*QRect name_rect(center_x - 7, y_offset - address_section_height / 2 - 17, 20, 20);
        std::string temp = *funcs.begin(); funcs.erase(funcs.begin());
        p.drawText(name_rect, Qt::AlignCenter, QString::fromStdString(temp)); */

    }

    QRect e_rect(start_x, y_offset, width / 3, 40);
    p.drawRect(e_rect);
    p.drawText(e_rect, Qt::AlignCenter, "C");

    p.drawLine(center_x, y_offset + 20, start_x, y_offset + 20);
    QRect name_rect(center_x - 5, y_offset + 4, 20, 20);
    p.drawText(name_rect, Qt::AlignCenter, "1");

    y_offset = start_y;
    // Рисуем выходы справа (0, 1, 2, ..., N)
    for (int i = 0; i < data_outputs; ++i) {
        QRect data_rect(start_x + 80, y_offset, width / 3, data_section_height);
        p.drawRect(data_rect);
        p.drawText(data_rect, Qt::AlignCenter, QString::number(i));
        y_offset += data_section_height;

        // Линия соединения данных с центральной линией
        /*p.drawLine(center_x + 80, y_offset - data_section_height / 2, start_x, y_offset - data_section_height / 2);
        QRect name_rect(center_x - 1, y_offset - address_section_height / 2 - 3, 10, 10);
        /*std::string temp = truth_table.back(); truth_table.pop_back();
        p.drawText(name_rect, Qt::AlignCenter, QString::fromStdString(temp)); */
    }

    // Средняя секция (обозначение шифратора)
    QRect center_rect(start_x + width / 3, start_y, width / 3, total_height);
    p.drawRect(center_rect);
    p.drawText(center_rect, Qt::AlignCenter, "DC");
}

