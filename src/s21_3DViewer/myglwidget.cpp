#include "myglwidget.h"

#include <stdlib.h>

#include <QDebug>

#include "mainwindow.h"

MyGLWidget::MyGLWidget(QWidget *parrent) : QOpenGLWidget(parrent) {}

void MyGLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void MyGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void MyGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //    glMatrixMode(GL_MODELVIEW);
  //    glLoadIdentity();
  glPointSize(5);
  //    glTranslated(0, 0, -3);
  glBegin(GL_POINTS);
  qDebug() << "V count: " << new_state.v_count;
  for (size_t i = 0; i != new_state.v_count; ++i) {
    qDebug() << new_state.v_array[i].x << new_state.v_array[i].y
             << new_state.v_array[i].z;
    glVertex3d(new_state.v_array[i].x, new_state.v_array[i].y,
               new_state.v_array[i].z);
  }
  glEnd();
}

void MyGLWidget::GoParse() {
  auto str = path.toStdString();
  parse_obj_file(str.c_str(), &initial_state);

  // need to move in C part
  new_state = initial_state;
  new_state.v_array = (point_t *)malloc(new_state.v_count * sizeof(point_t));
  for (uint64_t i = 0; i < new_state.v_count; ++i) {
    new_state.v_array[i] = initial_state.v_array[i];
  }
  // need to move in C part

  update();
}

void MyGLWidget::ResizeObject(double value) {
  scale_object(&new_state, value);  // need new!!@@@!@3131! object
  //    rotate_ox_object(&new_object, 0.5);
  //    rotate_oy_object(&new_object, 0.5);
  update();
}

void MyGLWidget::UpdateObject(ObjectParameters *params) {
  for (uint64_t i = 0; i < new_state.v_count; ++i) {
    new_state.v_array[i] = initial_state.v_array[i];
    rotate_ox_point(new_state.v_array + i, params->rotate_x);
    rotate_oy_point(new_state.v_array + i, params->rotate_y);
    rotate_oz_point(new_state.v_array + i, params->rotate_z);
    scale_point(new_state.v_array + i, params->scale);

    translate_point(new_state.v_array + i, X_AXIS, params->translate_x);
    translate_point(new_state.v_array + i, Y_AXIS, params->translate_y);
    translate_point(new_state.v_array + i, Z_AXIS, params->translate_z);
  }

  update();
}
