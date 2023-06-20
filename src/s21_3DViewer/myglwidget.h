#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QtMath>

extern "C" {
#include "../backend/3d_viewer.h"
}

class MyGLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  MyGLWidget(QWidget *parent = nullptr);
  QString path = NULL;
  object_t new_object = {0, 0, NULL, NULL};
  double trans_x = 0;
  double trans_y = 0;
  double trans_z = 0;
  double rotate_x = 0;
  double rotate_y = 0;
  double rotate_z = 0;
  double scale = 0;

 public slots:
//  void setXRotation(int angle);
//  void setYRotation(int angle);
//  void setZRotation(int angle);
  void GoParse();

 signals:
//  void xRotationChanged(int angle);
//  void yRotationChanged(int angle);
//  void zRotationChanged(int angle);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
//  void mousePressEvent(QMouseEvent *event) override;
//  void mouseMoveEvent(QMouseEvent *event) override;
};

#endif  // MYGLWIDGET_H
