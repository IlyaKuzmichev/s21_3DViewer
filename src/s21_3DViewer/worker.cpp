#include "worker.h"

Worker::Worker(QObject *parent, object_t& initial_state, object_t& new_state)
    : QObject{parent}, initial_state_(initial_state), new_state_(new_state) {
}

void Worker::Calculate(ObjectParameters *params, int id, int total) {
    uint64_t interval = new_state_.v_count / total;
    uint64_t begin = id * interval;
    uint64_t end = (id + 1) * interval;
    for (auto i = begin; i < end; ++i) {
        new_state_.v_array[i] = initial_state_.v_array[i];
        rotate_ox_point(new_state_.v_array + i, params->rotate_x);
        rotate_oy_point(new_state_.v_array + i, params->rotate_y);
        rotate_oz_point(new_state_.v_array + i, params->rotate_z);
        scale_point(new_state_.v_array + i, params->scale);

        translate_point(new_state_.v_array + i, X_AXIS, params->translate_x);
        translate_point(new_state_.v_array + i, Y_AXIS, params->translate_y);
        translate_point(new_state_.v_array + i, Z_AXIS, params->translate_z);
    }

    emit workerReady();
}
