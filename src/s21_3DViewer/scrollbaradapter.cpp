#include "scrollbaradapter.h"

#include <QLineEdit>

void ScrollBarAdapter::on_line_translate_returnPressed() {
    int prev_value = scroll_bar_->value();

    scroll_bar_->setValue(sender()->property("text").toInt());

    int next_value = scroll_bar_->value();
    if (prev_value == next_value) {
        emit scroll_bar_->valueChanged(next_value);
    }
}

