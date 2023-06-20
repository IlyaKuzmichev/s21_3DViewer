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

#pragma once

#include "3d_viewer.h"

/**
 * parse_error
 * @brief Enumeration of errors, occured in parsing
 */
enum parse_error {
  /// file cannot be opened
  cannot_open_file,
  /// format of file is incorrect
  incorrect_format,
  /// error in allocation of memory
  memory_allocation_error,
  /// all are right!
  status_ok
};

/**
 * @brief Fucntion for parsing .obj file
 *
 * @param[in] path - null-terminated string that contains path to .obj file
 * @param[out] obj - result of parsing process
 *
 * @return error code of parsing (check enum parse_error)
 */
int parse_obj_file(const char *path, object_t *obj);
