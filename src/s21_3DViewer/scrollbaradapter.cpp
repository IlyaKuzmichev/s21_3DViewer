#include "scrollbaradapter.h"

#include <QLineEdit>

void ScrollBarAdapter::onLineTranslateReturnPressed() {
  int prev_value = scroll_bar_->value();

  scroll_bar_->setValue(sender()->property("text").toInt());

  int next_value = scroll_bar_->value();
  if (prev_value == next_value) {
    emit scroll_bar_->valueChanged(next_value);
  } else {
      emit valueReallyChanged();
  }
}

void ScrollBarAdapter::onLineRotateReturnPressed() {
  int prev_value = scroll_bar_->value();

  int value = sender()->property("text").toInt();
  if (value > 0) {
    value = (value + 180) % 360 - 180;
  } else {
    value = (value - 180) % 360 + 180;
  }
  scroll_bar_->setValue(value);

  int next_value = scroll_bar_->value();
  if (prev_value == next_value) {
    emit scroll_bar_->valueChanged(next_value);
  } else {
      emit valueReallyChanged();
  }
}
