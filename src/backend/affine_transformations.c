#include <math.h>

#include "3d_viewer.h"

void translate_object(object_t* obj, axis_t axis, double shift) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    obj->v_array[i].arr[axis] += shift;
  }
}

void rotate_ox_object(object_t* obj, double angle) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    double y = obj->v_array[i].y;
    double z = obj->v_array[i].z;
    obj->v_array[i].y = y * cos(angle) - z * sin(angle);
    obj->v_array[i].z = y * sin(angle) + z * cos(angle);
  }
}

void rotate_oy_object(object_t* obj, double angle) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    double x = obj->v_array[i].x;
    double z = obj->v_array[i].z;
    obj->v_array[i].x = x * cos(angle) + z * sin(angle);
    obj->v_array[i].z = -x * sin(angle) + z * cos(angle);
  }
}

void rotate_oz_object(object_t* obj, double angle) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    double x = obj->v_array[i].x;
    double y = obj->v_array[i].y;
    obj->v_array[i].x = x * cos(angle) - y * sin(angle);
    obj->v_array[i].y = x * sin(angle) + y * cos(angle);
  }
}

void scale_object(object_t* obj, double scale) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    obj->v_array[i].x *= scale;
    obj->v_array[i].y *= scale;
    obj->v_array[i].z *= scale;
  }
}