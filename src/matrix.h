#ifndef MLLHEP_SRC_MATRIX_H
#define MLLHEP_SRC_MATRIX_H

#include "types.h"
#include "alloc/arena.h"

/* Dense f64 vector. */
typedef struct {
    usize len;
    f64 *data;
} Vec;

/* Dense f64 matrix, row-major: element (r, c) is data[r * cols + c]. */
typedef struct {
    usize rows;
    usize cols;
    f64 *data;
} Mat;

/* Storage is arena-backed, so there is no per-object free. Reclaim in bulk
   with arena_reset or arena_reset_to on the owning arena. */
Vec vec_alloc(Arena *a, usize len);
Vec vec_zeros(Arena *a, usize len);

Mat mat_alloc(Arena *a, usize rows, usize cols);
Mat mat_zeros(Arena *a, usize rows, usize cols);

static inline f64 mat_get(const Mat *m, usize r, usize c) {
    return m->data[r * m->cols + c];
}

static inline void mat_set(Mat *m, usize r, usize c, f64 v) {
    m->data[r * m->cols + c] = v;
}

static inline f64 *mat_row(const Mat *m, usize r) {
    return m->data + r * m->cols;
}

#endif /* MLLHEP_SRC_MATRIX_H */
