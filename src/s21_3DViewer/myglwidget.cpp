#include "myglwidget.h"
#include "mainwindow.h"
#include <QDebug>


MyGLWidget::MyGLWidget(QWidget* parrent) : QOpenGLWidget(parrent) {
}

void MyGLWidget::initializeGL() {

    glEnable(GL_DEPTH_TEST);
}

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
    qDebug() << "V count: " << new_object.v_count;
    for (size_t i = 0; i != new_object.v_count; ++i) {
        glVertex3d(new_object.v_array[i].x, new_object.v_array[i].y, new_object.v_array[i].z);
    }
    glEnd();
}

void MyGLWidget::GoParse() {
    auto str = path.toStdString();
    parse_obj_file(str.c_str(), &new_object);
    update();
}

void MyGLWidget::ResizeObject(double value) {
    scale_object(&new_object, value); // need new!!@@@!@3131! object
    //    rotate_ox_object(&new_object, 0.5);
    //    rotate_oy_object(&new_object, 0.5);
    update();
}
