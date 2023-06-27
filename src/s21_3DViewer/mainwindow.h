#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

extern "C" {
#include "../backend/3d_viewer.h"
#include "../backend/parser.h"
}

#include "ObjectParameters.h"
#include "lineeditadapter.h"
#include "scrollbaradapter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void SaveSettings();
  void LoadSettings();

 signals:
  void repaintObject(ObjectParameters *params);

 private slots:
  void on_button_open_clicked();

  void on_line_scale_returnPressed();

  void on_scroll_scale_valueChanged(int value);

  void on_pushButton_edges_colour_pressed();

  void on_pushButton_vertices_colour_pressed();

  void on_pushButton_bg_colour_pressed();

  void updateParams(int);

  void on_radioButton_parallel_pressed();

  void on_radioButton_central_pressed();

  void setMouseRotation(double x, double y);

  void setWheelScale(int increase_scale);

private:
  Ui::MainWindow *ui;
  std::vector<std::unique_ptr<ScrollBarAdapter>> scrollBarAdapters;
  std::vector<std::unique_ptr<LineEditAdapter>> lineEditAdapters;
  ObjectParameters params = {};

 signals:
  void openFile();
};
#endif  // MAINWINDOW_H
