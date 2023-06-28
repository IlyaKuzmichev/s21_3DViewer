#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QtMath>
#include <QLineEdit>

#include "ObjectParameters.h"

extern "C" {
#include "../backend/3d_viewer.h"
}

class MyGLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  MyGLWidget(QWidget *parent = nullptr);
  QString path = NULL;
  object_t initial_state = {0};
  object_t normalized_state = {0};
  object_t new_state = {0};
  QColor bg_colour;
  QColor edges_colour;
  QColor vertices_colour;
  bool is_edges_solid;
  bool is_parallel_projection;
  QLineEdit *vertices_count;
  QLineEdit *edges_count;

 private:
  QPoint lastPos;
  void setProjection();
  void free_memory(object_t* obj);

 public slots:
  void GoParse();
  void UpdateObject(ObjectParameters *params);
  void updateFrame();

 signals:
  void mouseTrigger(double x, double y);
  void wheelTrigger(int increase_scale);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent* event) override;

};

#endif  // MYGLWIDGET_H
