#include "mainwindow.h"

#include <QFileDialog>
#include <QOpenGLWidget>
#include <QColorDialog>
#include <QAbstractSlider>

#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

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

void MainWindow::on_scroll_translate_x_sliderMoved(int position) {
  ui->line_translate_x->setText(QString::number(position));
}

void MainWindow::on_line_translate_x_returnPressed() {
  ui->scroll_translate_x->setValue(ui->line_translate_x->text().toInt());
}

void MainWindow::on_scroll_translate_y_sliderMoved(int position)
{
    ui->line_translate_y->setText(QString::number(position));
}


void MainWindow::on_line_translate_y_returnPressed()
{
    ui->scroll_translate_y->setValue(ui->line_translate_y->text().toInt());
}


void MainWindow::on_scroll_translate_z_sliderMoved(int position)
{
     ui->line_translate_z->setText(QString::number(position));
}


void MainWindow::on_line_translate_z_returnPressed()
{
    ui->scroll_translate_z->setValue(ui->line_translate_z->text().toInt());
}


void MainWindow::on_scroll_rotate_x_sliderMoved(int position)
{
    ui->line_rotate_x->setText(QString::number(position));
}


void MainWindow::on_line_rotate_x_returnPressed()
{
    int num = ui->line_rotate_x->text().toInt();
    num =  num > 0 ? (num + 180) % 360 - 180 : (num - 180) % 360 + 180;
    ui->scroll_rotate_x->setValue(num);
    ui->line_rotate_x->setText(QString::number(num));
}


void MainWindow::on_scroll_rotate_y_sliderMoved(int position)
{
    ui->line_rotate_y->setText(QString::number(position));
}


void MainWindow::on_line_rotate_y_returnPressed()
{
    int num = ui->line_rotate_y->text().toInt();
    num =  num > 0 ? (num + 180) % 360 - 180 : (num - 180) % 360 + 180;
    ui->scroll_rotate_y->setValue(num);
    ui->line_rotate_y->setText(QString::number(num));
}


void MainWindow::on_scroll_rotate_z_sliderMoved(int position)
{
    ui->line_rotate_z->setText(QString::number(position));
}


void MainWindow::on_line_rotate_z_returnPressed()
{
    int num = ui->line_rotate_z->text().toInt();
    num =  num > 0 ? (num + 180) % 360 - 180 : (num - 180) % 360 + 180;
    ui->scroll_rotate_z->setValue(num);
    ui->line_rotate_z->setText(QString::number(num));
}


void MainWindow::on_scroll_scale_sliderMoved(int position)
{
    ui->line_scale->setText(QString::number(pow(10., static_cast<double>(position / 10.))));
}




void MainWindow::on_line_scale_returnPressed()
{
    ui->scroll_scale->setValue(static_cast<int>(10. * log10(ui->line_scale->text().toDouble())));
}

void MainWindow::on_pushButton_edges_colour_pressed()
{
    QColor new_colour = QColorDialog::getColor();
}


void MainWindow::on_pushButton_vertices_colour_pressed()
{
    QColor new_colour = QColorDialog::getColor();
}



void MainWindow::on_pushButton_bg_colour_pressed()
{
    QColor new_colour = QColorDialog::getColor();
}

