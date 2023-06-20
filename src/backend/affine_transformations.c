#include <math.h>

#include "3d_viewer.h"

void translate_object(object_t* obj, axis_t axis, double shift) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    translate_point(&obj->v_array[i], axis, shift);
  }
}

void rotate_ox_object(object_t* obj, double angle) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    rotate_ox_point(&obj->v_array[i], angle);
  }
}

void rotate_oy_object(object_t* obj, double angle) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    rotate_oy_point(&obj->v_array[i], angle);
  }
}

void rotate_oz_object(object_t* obj, double angle) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    rotate_oz_point(&obj->v_array[i], angle);
  }
}

void scale_object(object_t* obj, double scale) {
  for (size_t i = 0; i < obj->v_count; ++i) {
    scale_point(&obj->v_array[i], scale);
  }
}

void translate_point(point_t* point, axis_t axis, double shift) {
  point->arr[axis] += shift;
}

void rotate_ox_point(point_t* point, double angle) {
  double y = point->y;
  double z = point->z;
  point->y = y * cos(angle) - z * sin(angle);
  point->z = y * sin(angle) + z * cos(angle);
}

void rotate_oy_point(point_t* point, double angle) {
  double x = point->x;
  double z = point->z;
  point->x = x * cos(angle) + z * sin(angle);
  point->z = -x * sin(angle) + z * cos(angle);
}

void rotate_oz_point(point_t* point, double angle) {
  double x = point->x;
  double y = point->y;
  point->x = x * cos(angle) - y * sin(angle);
  point->y = x * sin(angle) + y * cos(angle);
}

void scale_point(point_t* point, double scale) {
  point->x *= scale;
  point->y *= scale;
  point->z *= scale;
}