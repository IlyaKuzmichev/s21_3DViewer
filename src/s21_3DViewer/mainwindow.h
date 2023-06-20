#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern "C" {
#include "../backend/3d_viewer.h"
#include "../backend/parser.h"
}

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

 private slots:
  void on_button_open_clicked();

//  void slider_moved();

  void on_scroll_translate_x_sliderMoved(int position);

  void on_line_translate_x_returnPressed();

  void on_scroll_translate_y_sliderMoved(int position);

  void on_line_translate_y_returnPressed();

  void on_scroll_translate_z_sliderMoved(int position);

  void on_line_translate_z_returnPressed();

  void on_scroll_rotate_x_sliderMoved(int position);

  void on_line_rotate_x_returnPressed();

  void on_scroll_rotate_y_sliderMoved(int position);

  void on_line_rotate_y_returnPressed();

  void on_scroll_rotate_z_sliderMoved(int position);

  void on_line_rotate_z_returnPressed();

  void on_scroll_scale_sliderMoved(int position);

  void on_line_scale_returnPressed();

  void on_pushButton_edges_colour_pressed();

  void on_pushButton_vertices_colour_pressed();

  void on_pushButton_bg_colour_pressed();

private:
  Ui::MainWindow *ui;

signals:
  void openFile();
};
#endif  // MAINWINDOW_H
