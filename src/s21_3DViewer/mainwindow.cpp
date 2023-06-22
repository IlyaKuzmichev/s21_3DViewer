#include "mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QOpenGLWidget>
#include <initializer_list>
#include <tuple>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  for (auto obj_pair :
       {std::make_pair(ui->line_translate_x, ui->scroll_translate_x),
        std::make_pair(ui->line_translate_y, ui->scroll_translate_y),
        std::make_pair(ui->line_translate_z, ui->scroll_translate_z)}) {
    lineEditAdapters.push_back(LineEditAdapter::create(this, obj_pair.first));
    connect(obj_pair.second, SIGNAL(valueChanged(int)),
            lineEditAdapters.back().get(), SLOT(on_scroll_valueChanged(int)));

    scrollBarAdapters.push_back(
        ScrollBarAdapter::create(this, obj_pair.second));
    connect(obj_pair.first, SIGNAL(returnPressed()),
            scrollBarAdapters.back().get(),
            SLOT(on_line_translate_returnPressed()));
  }

  for (auto obj_pair :
       {std::make_pair(ui->line_rotate_x, ui->scroll_rotate_x),
        std::make_pair(ui->line_rotate_y, ui->scroll_rotate_y),
        std::make_pair(ui->line_rotate_z, ui->scroll_rotate_z)}) {
    lineEditAdapters.push_back(LineEditAdapter::create(this, obj_pair.first));
    connect(obj_pair.second, SIGNAL(valueChanged(int)),
            lineEditAdapters.back().get(), SLOT(on_scroll_valueChanged(int)));

    scrollBarAdapters.push_back(
        ScrollBarAdapter::create(this, obj_pair.second));
    connect(obj_pair.first, SIGNAL(returnPressed()),
            scrollBarAdapters.back().get(),
            SLOT(on_line_rotate_returnPressed()));
  }

  connect(this, &MainWindow::openFile, ui->GLWidget, &MyGLWidget::GoParse);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_button_open_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, "Open File", "/home",
                                                  "Object files (*.obj)");
  ui->line_filepath->setText(fileName);
  ui->GLWidget->path = fileName;
  ui->scroll_rotate_x->setValue(0);
  ui->scroll_rotate_y->setValue(0);
  ui->scroll_rotate_z->setValue(0);
  ui->scroll_translate_x->setValue(0);
  ui->scroll_translate_y->setValue(0);
  ui->scroll_translate_z->setValue(0);
  ui->scroll_scale->setValue(0);
  ui->line_vertex->setText("Get from GL Widget");
  ui->line_edge->setText("Need to count");

  emit openFile();
}

void MainWindow::on_scroll_scale_sliderMoved(int position) {
  ui->line_scale->setText(
      QString::number(pow(10., static_cast<double>(position / 10.))));
  ui->GLWidget->ResizeObject(ui->line_scale->text().toDouble());
}

void MainWindow::on_line_scale_returnPressed() {
  ui->scroll_scale->setValue(
      static_cast<int>(10. * log10(ui->line_scale->text().toDouble())));
  ui->GLWidget->ResizeObject(ui->line_scale->text().toDouble());
}

void MainWindow::on_pushButton_edges_colour_pressed() {
  QColor new_colour = QColorDialog::getColor();
}

void MainWindow::on_pushButton_vertices_colour_pressed() {
  QColor new_colour = QColorDialog::getColor();
}

void MainWindow::on_pushButton_bg_colour_pressed() {
  QColor new_colour = QColorDialog::getColor();
}
