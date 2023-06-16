#include "parser.h"

#include <stdio.h>
#include <string.h>

int parse_obj_file(char *path, object_t *obj) {
  enum parse_error result = status_ok;
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    result = cannot_open_file;
  } else {
    char *line = NULL;
    size_t linecapp = 0;
    ssize_t character_count = 0;
    obj->v_count = 0;
    obj->f_count = 0;
    obj->x_max = 0;
    obj->x_min = 0;
    obj->y_max = 0;
    obj->y_min = 0;
    while ((character_count = getline(&line, &linecapp, f)),
           character_count > 0) {
      if (strncmp(line, "v ", sizeof("v ") - 1u) == 0) {
        ++obj->v_count;
      } else if (strncmp(line, "f ", sizeof("f ") - 1u) == 0) {
        ++obj->f_count;
      }
    }

    obj->v_array = (point_t *)malloc(obj->v_count * sizeof(point_t));
    obj->f_array = (face_t *)malloc(obj->f_count * sizeof(face_t));
    if (obj->v_array == NULL || obj->f_array == NULL) {
      result = memory_allocation_error;
    } else {
      fseek(f, 0, SEEK_SET);
      size_t last_v_index = 0;
      size_t last_f_index = 0;
      while ((character_count = getline(&line, &linecapp, f)),
             character_count > 0) {
        if (strncmp(line, "v ", sizeof("v ") - 1u) == 0) {
          sscanf(line + sizeof("v ") - 1u, "%lf %lf %lf",
                 &obj->v_array[last_v_index].x, &obj->v_array[last_v_index].y,
                 &obj->v_array[last_v_index].z);
          ++last_v_index;
        } else if (strncmp(line, "f ", sizeof("f ") - 1u) == 0) {
          char *next_lf = strchr(line, ' ');
          long long int v_number = 0;
          size_t v_count = 0;
          while (next_lf != NULL && sscanf(next_lf, "%lld", &v_number) > 0) {
            next_lf = strchr(next_lf + 1, ' ');
            ++v_count;
          }
          obj->f_array[last_f_index].v_count = v_count;
          obj->f_array[last_f_index].v_array =
              (point_t **)malloc(v_count * sizeof(point_t *));

          if (obj->f_array[last_f_index].v_array == NULL) {
            result = memory_allocation_error;
          } else {
            next_lf = strchr(line, ' ');
            v_number = 0;
            v_count = 0;
            while (next_lf != NULL && sscanf(next_lf, "%lld", &v_number) > 0) {
              if (v_number < 0) {
                v_number = last_v_index - v_number;
              } else {
                v_number -= 1;
              }
              obj->f_array[last_f_index].v_array[v_count] =
                  &obj->v_array[v_number];
              next_lf = strchr(next_lf + 1, ' ');
              ++v_count;
            }
          }
          ++last_f_index;
        }
      }
    }
  }

  return result;
}
