#include <math.h>

#include "3d_viewer.h"

void translate_object(Object_t* obj, axis_t axis, double shift) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    obj->v_matrix[i * 3 + axis] += shift;
  }
}

void rotate_ox_object(Object_t* obj, double angle) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    double y = obj->v_matrix[i * 3 + 1];
    double z = obj->v_matrix[i * 3 + 2];
    obj->v_matrix[i * 3 + 1] = y * cos(angle) - z * sin(angle);
    obj->v_matrix[i * 3 + 1] = y * sin(angle) + z * cos(angle);
  }
}

void rotate_oy_object(Object_t* obj, double angle) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    double x = obj->v_matrix[i * 3];
    double z = obj->v_matrix[i * 3 + 2];
    obj->v_matrix[i * 3] = x * cos(angle) + z * sin(angle);
    obj->v_matrix[i * 3 + 2] = -x * sin(angle) + z * cos(angle);
  }
}

void rotate_oz_object(Object_t* obj, double angle) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    double x = obj->v_matrix[i * 3];
    double y = obj->v_matrix[i * 3 + 1];
    obj->v_matrix[i * 3] = x * cos(angle) - y * sin(angle);
    obj->v_matrix[i * 3 + 2] = x * sin(angle) + y * cos(angle);
  }
}

void scale_object(Object_t* obj, double scale) {
  for (size_t i = 0; i < 3 * obj->v_count; ++i) {
    obj->v_matrix[i] *= scale;
  }
}