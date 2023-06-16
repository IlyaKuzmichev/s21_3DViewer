#include "mainwindow.h"

#include <QFileDialog>
#include <QOpenGLWidget>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_button_open_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, "Open File", "/home",
                                                  "Object files (*.obj)");
  ui->line_filepath->setText(fileName);
}

void MainWindow::on_scroll_translate_x_sliderMoved(int position) {
  ui->line_translate_x->setText(QString::number(position));
}

void MainWindow::on_line_translate_x_returnPressed() {
  ui->scroll_translate_x->setValue(ui->line_translate_x->text().toInt());
}
