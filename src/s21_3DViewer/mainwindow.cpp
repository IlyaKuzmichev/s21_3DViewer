#include "mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QOpenGLWidget>
#include <QSettings>
#include <initializer_list>
#include <tuple>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  LoadSettings();

  for (auto obj_pair :
       {std::make_pair(ui->line_translate_x, ui->scroll_translate_x),
        std::make_pair(ui->line_translate_y, ui->scroll_translate_y),
        std::make_pair(ui->line_translate_z, ui->scroll_translate_z)}) {
    lineEditAdapters.push_back(LineEditAdapter::create(this, obj_pair.first));
    connect(obj_pair.second, SIGNAL(valueChanged(int)),
            lineEditAdapters.back().get(), SLOT(onScrollValueChanged(int)));
    connect(obj_pair.second, SIGNAL(valueChanged(int)), this, SLOT(updateParams(int)));

    scrollBarAdapters.push_back(
        ScrollBarAdapter::create(this, obj_pair.second));
    connect(obj_pair.first, SIGNAL(returnPressed()),
            scrollBarAdapters.back().get(),
            SLOT(onLineTranslateReturnPressed()));
  }

  for (auto obj_pair :
       {std::make_pair(ui->line_rotate_x, ui->scroll_rotate_x),
        std::make_pair(ui->line_rotate_y, ui->scroll_rotate_y),
        std::make_pair(ui->line_rotate_z, ui->scroll_rotate_z)}) {
    lineEditAdapters.push_back(LineEditAdapter::create(this, obj_pair.first));
    connect(obj_pair.second, SIGNAL(valueChanged(int)),
            lineEditAdapters.back().get(), SLOT(onScrollValueChanged(int)));
    connect(obj_pair.second, SIGNAL(valueChanged(int)), this, SLOT(updateParams(int)));

    scrollBarAdapters.push_back(
        ScrollBarAdapter::create(this, obj_pair.second));
    connect(obj_pair.first, SIGNAL(returnPressed()),
            scrollBarAdapters.back().get(),
            SLOT(onLineRotateReturnPressed()));
  }
  connect(ui->scroll_scale, SIGNAL(valueChanged(int)), this, SLOT(updateParams(int)));
  connect(this, &MainWindow::openFile, ui->GLWidget, &MyGLWidget::GoParse);
  connect(this, SIGNAL(repaintObject(ObjectParameters*)), ui->GLWidget, SLOT(UpdateObject(ObjectParameters*)));
  connect(ui->GLWidget, &MyGLWidget::mouseTrigger, this, &MainWindow::setMouseRotation);

  // this is BAD code
  ui->GLWidget->vertices_count = ui->line_vertex;
  ui->GLWidget->edges_count = ui->line_edge;
  // this is BAD code
}

MainWindow::~MainWindow() {
    SaveSettings();
    delete ui;
}

void MainWindow::SaveSettings() {
    QSettings settings("Aboba Team", "3DViewer");
    settings.setValue("bg_colour", ui->GLWidget->bg_colour);
    settings.setValue("projection", ui->GLWidget->is_parallel_projection);
}

void MainWindow::setMouseRotation(double x, double y) {
    ui->line_rotate_x->setText(QString::number(ui->scroll_rotate_x->value() + static_cast<int>(x * 3. / 20.)));
    emit ui->line_rotate_x->returnPressed();

    ui->line_rotate_y->setText(QString::number(ui->scroll_rotate_y->value() + static_cast<int>(y * 3. / 20.)));
    emit ui->line_rotate_y->returnPressed();
}

void MainWindow::LoadSettings() {
    QSettings settings("Aboba Team", "3DViewer");
    ui->GLWidget->bg_colour = settings.value("bg_colour", QColor(Qt::black)).value<QColor>();
    ui->GLWidget->is_parallel_projection = settings.value("projection", true).value<bool>();
    if (ui->GLWidget->is_parallel_projection == false) {
        ui->radioButton_central->setChecked(true);
    }

//    QString filePath = settings.fileName();
//    qDebug() << filePath;
}

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

void MainWindow::on_scroll_scale_valueChanged(int value)
{
    ui->line_scale->setText(
        QString::number(pow(10., static_cast<double>(value / 10.))));
}

void MainWindow::on_line_scale_returnPressed()
{
    ui->scroll_scale->setValue(
        static_cast<int>(10. * log10(ui->line_scale->text().toDouble())));
}

void MainWindow::on_pushButton_edges_colour_pressed() {
  QColor new_colour = QColorDialog::getColor();
}

void MainWindow::on_pushButton_vertices_colour_pressed() {
  QColor new_colour = QColorDialog::getColor();
}

void MainWindow::on_pushButton_bg_colour_pressed() {
   ui->GLWidget->bg_colour = QColorDialog::getColor();
}

void MainWindow::updateParams(int) {
    params.translate_x = static_cast<double>(ui->scroll_translate_x->value()) / 100.;
    params.translate_y = static_cast<double>(ui->scroll_translate_y->value()) / 100.;
    params.translate_z = static_cast<double>(ui->scroll_translate_z->value()) / 100.;

    params.rotate_x = ui->scroll_rotate_x->value() / 180.0 * M_PI;
    params.rotate_y = ui->scroll_rotate_y->value() / 180.0 * M_PI;
    params.rotate_z = ui->scroll_rotate_z->value() / 180.0 * M_PI;

    params.scale = ui->line_scale->text().toDouble();

    emit repaintObject(&params);
}

void MainWindow::on_radioButton_parallel_pressed()
{
    ui->GLWidget->is_parallel_projection = true;
}



void MainWindow::on_radioButton_central_pressed()
{
    ui->GLWidget->is_parallel_projection = false;
}

