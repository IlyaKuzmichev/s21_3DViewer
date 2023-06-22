#include "lineeditadapter.h"

void LineEditAdapter::on_scroll_valueChanged(int value) {
  line_edit_->setText(QString::number(value));
}
