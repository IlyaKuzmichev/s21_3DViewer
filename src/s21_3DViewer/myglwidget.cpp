#include "myglwidget.h"

#include <stdlib.h>

#include <QDebug>

#include "mainwindow.h"

MyGLWidget::MyGLWidget(QWidget *parrent) : QOpenGLWidget(parrent) {}

void MyGLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
//    glOrtho(-10, 10, -10, 10, 1, 1000);
//    glViewport(0, 0, 1200, 1200);
}

void MyGLWidget::resizeGL(int w, int h) {
  glMatrixMode(GL_PROJECTION); // устанавливает текущей проекционную матрицу
  glLoadIdentity();            // присваивает проекционной матрице единичную матрицу
// мировое окно
  glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 1.0);     // параметры видимости ортогональной проекции
// плоскости отсечения (левая, правая, верхняя, нижняя, передняя, задняя)
//  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0); // параметры видимости перспективной проекции
// плоскости отсечения: (левая, правая, верхняя, нижняя, ближняя, дальняя)

  // поле просмотра
  glViewport(0, 0, (GLint)w, (GLint)h); // устанавливает видовое окно с размерами равными окну виджета
}

void MyGLWidget::paintGL() {
  // glClear(GL_COLOR_BUFFER_BIT); // окно виджета очищается текущим цветом очистки
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера изображения и глубины
  glMatrixMode(GL_MODELVIEW); // устанавливает положение и ориентацию матрице моделирования
  glLoadIdentity();           // загружает единичную матрицу моделирования
  glPointSize(5);
  glBegin(GL_POINTS);
//  qDebug() << "V count: " << new_state.v_count;
  for (size_t i = 0; i != new_state.v_count; ++i) {
//    qDebug() << new_state.v_array[i].x << new_state.v_array[i].y
//             << new_state.v_array[i].z;
    glVertex3d(new_state.v_array[i].x, new_state.v_array[i].y,
               new_state.v_array[i].z);
  }
  glEnd();
}

void MyGLWidget::GoParse() {
  auto str = path.toStdString();
  parse_obj_file(str.c_str(), &initial_state);
  normalize_object(initial_state, &normalized_state);
  // need to move in C part
  new_state = normalized_state;
  new_state.v_array = (point_t *)malloc(new_state.v_count * sizeof(point_t));
  for (uint64_t i = 0; i < new_state.v_count; ++i) {
    new_state.v_array[i] = normalized_state.v_array[i];
  }
  // need to move in C part
//  resizeGL(1200, 1200);
  update();
}

//void MyGLWidget::ResizeObject(double value) {
//  scale_object(&new_state, value);  // need new!!@@@!@3131! object
//  //    rotate_ox_object(&new_object, 0.5);
//  //    rotate_oy_object(&new_object, 0.5);
//  update();
//}

void MyGLWidget::UpdateObject(ObjectParameters *params) {
  for (uint64_t i = 0; i < new_state.v_count; ++i) {
    new_state.v_array[i] = normalized_state.v_array[i];
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
