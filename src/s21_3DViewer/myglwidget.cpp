#include "myglwidget.h"

#include <stdlib.h>

#include <QDebug>

#include "mainwindow.h"

MyGLWidget::MyGLWidget(QWidget *parrent) : QOpenGLWidget(parrent) {}

void MyGLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
}

void MyGLWidget::resizeGL(int w, int h) {
}

void MyGLWidget::paintGL() {
  setProjection();
  glClearColor(bg_colour.redF(), bg_colour.greenF(), bg_colour.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера изображения и глубины
  glMatrixMode(GL_MODELVIEW); // устанавливает положение и ориентацию матрице моделирования
  glLoadIdentity();           // загружает единичную матрицу моделирования
  glPointSize(3);
  glBegin(GL_POINTS);
  for (size_t i = 0; i != new_state.v_count; ++i) {
//    qDebug() << new_state.v_array[i].x << new_state.v_array[i].y
//             << new_state.v_array[i].z;
    glVertex3d(new_state.v_array[i].x, new_state.v_array[i].y,
               new_state.v_array[i].z);
  }
  glEnd();
  for (size_t i = 0; i < initial_state.f_count; ++i) {
      const auto& face = initial_state.f_array[i];
      glBegin(GL_LINES);
      const auto& first_point = new_state.v_array[face.v_array[0]];
      glVertex3d(first_point.x, first_point.y, first_point.z);
      for (size_t j = 1; j < face.v_count; ++j) {
          const auto& point = new_state.v_array[face.v_array[j]];
          glVertex3d(point.x, point.y, point.z);
          glVertex3d(point.x, point.y, point.z);
      }
      glVertex3d(first_point.x, first_point.y, first_point.z);
      glEnd();
  }
}

void MyGLWidget::GoParse() {
  auto str = path.toStdString();
  free_memory(&initial_state);
  free_memory(&normalized_state);
  free_memory(&new_state);
  parse_obj_file(str.c_str(), &initial_state);
  normalize_object(initial_state, &normalized_state);
  // need to move in C part
  new_state = normalized_state;
  new_state.v_array = (point_t *)malloc(new_state.v_count * sizeof(point_t));
  for (uint64_t i = 0; i < new_state.v_count; ++i) {
    new_state.v_array[i] = normalized_state.v_array[i];
  }
  // need to move in C part

  // this is BAD code
  vertices_count->setText(QString::number(initial_state.v_count));
  edges_count->setText(QString::number(initial_state.e_count));
  // this is BAD code
  qDebug() << normalized_state.x_min << " " << normalized_state.x_max << " " << normalized_state.y_min << " " << normalized_state.y_max << '\n';
  update();
}

void MyGLWidget::free_memory(object_t* obj) {
//    if(NULL != obj->f_array) {
//        for (size_t i = 0; i < obj->f_count; ++i) {
//            if (NULL != obj->f_array[i].v_array)
//            delete[] obj->f_array[i].v_array;
//        }
//        delete[] obj->f_array;
//    }
//    if (NULL != obj->v_array) {
//        delete[] obj->v_array;
//    }
}

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

void MyGLWidget::mousePressEvent(QMouseEvent *event) {
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event) {
    double diff_x = event->pos().y() - lastPos.y();
    double diff_y = event->pos().x() - lastPos.x();
    lastPos = event->pos();
    emit mouseTrigger(diff_x, diff_y);
}

void MyGLWidget::wheelEvent(QWheelEvent* event) {
    int increase_scale = 5;
    if (event->angleDelta().y() < 0) {
        increase_scale = -5;
    }
    emit wheelTrigger(increase_scale);
}

void MyGLWidget::setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fov = 60.0 * M_PI / 180;
    GLfloat near = 1 / tan(fov / 2);
    if(is_parallel_projection) {
        glOrtho(-2., 2., -2., 2., -10, 1.);
    } else {
        glFrustum(-0.5, 0.5, -0.5, 0.5, near, 10.);
        glTranslated(0, 0, -near * 3);
    }
}

void MyGLWidget::updateFrame() {
    update();
}
