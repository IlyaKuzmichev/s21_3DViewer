/* ==========================================================================*/
/* Copyright 2023 © Moscow, Russian Federaion
 *
 * This file contains Original Code created by
 * Michail Kopylov aka sarellad,
 * Igor Baidikov aka lorenttr,
 * Ilya Kuzmichev aka wilmerno.
 *
 * The Original Code and all software developed in the process of
 * participation on learning by experimental programming educational method.
 * The whole methodology was developed and distributed by
 * Autonomous non-profit organization «School 21» (ANO «School 21»).
 *
 * Redistribution and use of this file, its parts, or entire project
 * are permitted by confirmation of its original creators.
 */
/* ==========================================================================*/

/**
 * @author sarellad, lorenttr & wilmerno
 * @mainpage
 * 3dViewer_v1.0, backend realised in C language, gui written
 * on QT Creator
 *
 * Implementation of a program to visualise 3D wireframe models
 *
 * The program provide the ability to:
 * Load a wireframe model from an obj file (vertices and surfaces list support
 * only). Translate the model by a given distance in relation to the X, Y, Z
 * axes. Rotate the model by a given angle relative to its X, Y, Z axes. Scale
 * the model by a given value.
 *
 * The program allow customizing the type of projection (parallel and central)
 * The program allow setting up the type (solid, dashed), color and thickness
 * of the edges, display method (none, circle, square), color and size of the
 * vertices
 * The program allow choosing the background color
 * Settings saved between program restarts
 *
 * The program allow saving the captured (rendered) images as bmp and jpeg
 * files. The program allow recording small screencasts by a special button -
 * the current custom affine transformation of the loaded object into
 * gif-animation (640x480, 10fps, 5s)
 */

#pragma once

#include <stdlib.h>
/**
 * point_t
 * @brief Union for point structure
 */
typedef union point_u {
  double arr[3];  ///> to call as array
  struct {
    double x;  ///> x coord
    double y;  ///> y coord
    double z;  ///> z coord
  };
} point_t;

/**
 * face_t
 * @brief face's structure with various points quantity
 */
typedef struct face_s {
  uint64_t v_count;   ///> quantity of faces
  point_t** v_array;  ///> dynamicly allocated array of points
} face_t;

/**
 * object_t
 * @brief Parsed .obj structure
 */
typedef struct object_s {
  uint64_t v_count;                   ///> number of vertexes
  uint64_t f_count;                   ///> number of faces
  double x_min, x_max, y_min, y_max;  ///> limit values of the object
  point_t* v_array;  ///> matrice of vertexes (each point has 3 coordinates)
  face_t* f_array;   ///> array of faces
} object_t;

/**
 * axis_t
 * @brief enum axes, with which it is convenient to iterate over an array of
 * points (index + axis == x, y or z coordinate of the point)
 */
typedef enum axis_t { X_AXIS = 0, Y_AXIS, Z_AXIS } axis_t;

// Affine transformations

/**
 * @brief Fucntion fo translate model by a given distance
 *
 * @param obj --- pointer to object structure
 * @param axis --- x, y or z
 * @param shift --- value of the shift
 */
void translate_object(object_t* obj, axis_t axis, double shift);

/**
 * @brief Fucntion fo rotate model by a given angle relative to its X axis
 *
 * @param obj - pointer to object structure
 * @param angle - value of the angle to rotate
 */
void rotate_ox_object(object_t* obj, double angle);

/**
 * @brief Fucntion fo rotate model by a given angle relative to its Y axis
 *
 * @param obj - pointer to object structure
 * @param angle - value of the angle to rotate
 */
void rotate_oy_object(object_t* obj, double angle);

/**
 * @brief Fucntion fo rotate model by a given angle relative to its Z axis
 *
 * @param obj - pointer to object structure
 * @param angle - value of the angle to rotate
 */
void rotate_oz_object(object_t* obj, double angle);

/**
 * @brief Fucntion fo scale model by a given value
 *
 * @param obj - pointer to object structure
 * @param scale - value to scale
 */
void scale_object(object_t* obj, double scale);
