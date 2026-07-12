#include "matrix.h"

#include <string.h>

Vec vec_alloc(Arena *a, usize len) {
    Vec v;
    v.len = len;
    v.data = (f64 *)arena_alloc(a, len * sizeof(f64));
    return v;
}

Vec vec_zeros(Arena *a, usize len) {
    Vec v = vec_alloc(a, len);
    memset(v.data, 0, len * sizeof(f64));
    return v;
}

Mat mat_alloc(Arena *a, usize rows, usize cols) {
    Mat m;
    m.rows = rows;
    m.cols = cols;
    m.data = (f64 *)arena_alloc(a, rows * cols * sizeof(f64));
    return m;
}

Mat mat_zeros(Arena *a, usize rows, usize cols) {
    Mat m = mat_alloc(a, rows, cols);
    memset(m.data, 0, rows * cols * sizeof(f64));
    return m;
}
