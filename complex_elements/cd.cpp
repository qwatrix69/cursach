#include "cd.h"

Cd::Cd(int count_inputs, std::string func, std::string oper1, std::string oper2, QWidget *parent)
    : QWidget(parent), func_type(func), oper1(oper1), oper2(oper2) {
    address_inputs = count_inputs * 2;
    data_outputs = count_inputs;
    setFixedSize(200, 25 * address_inputs + 40 * data_outputs + 50 + 10);
}

void Cd::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    int address_section_height = 25;
    int data_section_height = (address_inputs * 25 + 40) / data_outputs;
    int start_x = 10, start_y = 10;
    int width = 120;
    int total_height = address_inputs * address_section_height + 40;

    QPainterPath path;
    QRect rect(start_x, start_y, width, total_height);
    path.addRect(rect);
    p.setPen(Qt::black);
    p.drawPath(path);

    std::vector<std::string> truth_table;

    if (func_type == "&" or func_type == "+" or func_type == "-" or func_type == "^") {
        truth_table = {"0", "1"};
    }
    else if (func_type == "|" or func_type == "/") {
        truth_table = {"1", "0"};
    }

    int center_x = start_x - 10;
    int y_offset = start_y;
    for (int i = 1; i < data_outputs + 1; ++i) {
        QRect data_rect(start_x + 80, y_offset, width / 3, data_section_height);
        p.drawRect(data_rect);
        p.drawText(data_rect, Qt::AlignCenter, QString::number(i));
        y_offset += data_section_height;
    }

    y_offset = start_y;
    for (int i = 0; i < address_inputs; ++i) {
        QRect addr_rect(start_x, y_offset, width / 3, address_section_height);
        p.drawRect(addr_rect);
        p.drawText(addr_rect, Qt::AlignCenter, QString::number(i));
        y_offset += address_section_height;

        if (i == 0 or i == 1) {
            p.drawLine(center_x, y_offset - address_section_height / 2, start_x, y_offset - address_section_height / 2);
            QRect name_rect(center_x - 1, y_offset - data_section_height / 2 + 8, 10, 10);
            std::string temp = truth_table.back(); truth_table.pop_back();
            p.drawText(name_rect, Qt::AlignCenter, QString::fromStdString(temp));
        }
    }

    QRect e_rect(start_x, y_offset, width / 3, 40);
    p.drawRect(e_rect);
    p.drawText(e_rect, Qt::AlignCenter, "C");

    p.drawLine(center_x, y_offset + 20, start_x, y_offset + 20);
    QRect name_rect(center_x - 5, y_offset + 4, 20, 20);
    p.drawText(name_rect, Qt::AlignCenter, "1");

    QRect center_rect(start_x + width / 3, start_y, width / 3, total_height);
    p.drawRect(center_rect);
    p.drawText(center_rect, Qt::AlignCenter, "CD");
}

