#include "matrix.h"

#include <assert.h>
#include <math.h>
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

Mat mat_add(Arena *a, const Mat *x, const Mat *y) {
    assert(x->rows == y->rows && x->cols == y->cols);
    Mat r = mat_alloc(a, x->rows, x->cols);
    usize n = x->rows * x->cols;
    for (usize i = 0; i < n; i++) {
        r.data[i] = x->data[i] + y->data[i];
    }
    return r;
}

Mat mat_sub(Arena *a, const Mat *x, const Mat *y) {
    assert(x->rows == y->rows && x->cols == y->cols);
    Mat r = mat_alloc(a, x->rows, x->cols);
    usize n = x->rows * x->cols;
    for (usize i = 0; i < n; i++) {
        r.data[i] = x->data[i] - y->data[i];
    }
    return r;
}

Mat mat_scale(Arena *a, const Mat *x, f64 s) {
    Mat r = mat_alloc(a, x->rows, x->cols);
    usize n = x->rows * x->cols;
    for (usize i = 0; i < n; i++) {
        r.data[i] = x->data[i] * s;
    }
    return r;
}

Mat mat_matmul(Arena *a, const Mat *x, const Mat *y) {
    assert(x->cols == y->rows);
    Mat r = mat_zeros(a, x->rows, y->cols);
    /* ikj order keeps the inner loop sequential over both y and r rows */
    for (usize i = 0; i < x->rows; i++) {
        for (usize k = 0; k < x->cols; k++) {
            f64 xik = x->data[i * x->cols + k];
            const f64 *yrow = y->data + k * y->cols;
            f64 *rrow = r.data + i * r.cols;
            for (usize j = 0; j < y->cols; j++) {
                rrow[j] += xik * yrow[j];
            }
        }
    }
    return r;
}

Mat mat_transpose(Arena *a, const Mat *x) {
    Mat r = mat_alloc(a, x->cols, x->rows);
    for (usize i = 0; i < x->rows; i++) {
        for (usize j = 0; j < x->cols; j++) {
            r.data[j * r.cols + i] = x->data[i * x->cols + j];
        }
    }
    return r;
}

f64 vec_dot(const Vec *x, const Vec *y) {
    assert(x->len == y->len);
    f64 s = 0.0;
    for (usize i = 0; i < x->len; i++) {
        s += x->data[i] * y->data[i];
    }
    return s;
}

f64 vec_norm1(const Vec *x) {
    f64 s = 0.0;
    for (usize i = 0; i < x->len; i++) {
        s += fabs(x->data[i]);
    }
    return s;
}

f64 vec_norm2(const Vec *x) {
    return sqrt(vec_dot(x, x));
}

Vec vec_mul(Arena *a, const Vec *x, const Vec *y) {
    assert(x->len == y->len);
    Vec r = vec_alloc(a, x->len);
    for (usize i = 0; i < x->len; i++) {
        r.data[i] = x->data[i] * y->data[i];
    }
    return r;
}

Vec vec_div(Arena *a, const Vec *x, const Vec *y) {
    assert(x->len == y->len);
    Vec r = vec_alloc(a, x->len);
    for (usize i = 0; i < x->len; i++) {
        r.data[i] = x->data[i] / y->data[i];
    }
    return r;
}

Mat mat_outer(Arena *a, const Vec *x, const Vec *y) {
    Mat r = mat_alloc(a, x->len, y->len);
    for (usize i = 0; i < x->len; i++) {
        f64 xi = x->data[i];
        f64 *rrow = r.data + i * r.cols;
        for (usize j = 0; j < y->len; j++) {
            rrow[j] = xi * y->data[j];
        }
    }
    return r;
}
