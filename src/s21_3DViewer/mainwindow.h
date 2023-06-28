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

enum DisplayMethod {
    none = 0,
    circle,
    square
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void SaveSettings();
  void LoadSettings();

 signals:
  void repaintObject(ObjectParameters *params);

  void updateWidget();

 private slots:
  void on_button_open_clicked();

  void on_line_scale_returnPressed();

  void on_scroll_scale_valueChanged(int value);

  void on_pushButton_edges_colour_pressed();

  void on_pushButton_vertices_colour_pressed();

  void on_pushButton_bg_colour_pressed();

  void updateParams(int);

  void setMouseRotation(double x, double y);

  void setWheelScale(int increase_scale);

  void on_radioButton_parallel_toggled(bool checked);

  void on_radioButton_edges_solid_toggled(bool checked);

  void on_slider_thickness_valueChanged(int value);

  void on_radioButton_display_none_pressed();

  void on_radioButton_display_circle_pressed();

  void on_radioButton_display_square_pressed();

  void on_slider_size_valueChanged(int value);

private:
  Ui::MainWindow *ui;
  std::vector<std::unique_ptr<ScrollBarAdapter>> scrollBarAdapters;
  std::vector<std::unique_ptr<LineEditAdapter>> lineEditAdapters;
  ObjectParameters params = {};
  void groupButtons();

 signals:
  void openFile();
};
#endif  // MAINWINDOW_H
