#include "test.h"
#include "src/matrix.h"
#include "alloc/arena.h"

int main(void) {
    Arena a = arena_create(0);

    Mat m = mat_zeros(&a, 2, 3);
    CHECK(m.rows == 2);
    CHECK(m.cols == 3);
    CHECK(mat_get(&m, 1, 2) == 0.0);

    mat_set(&m, 1, 2, 4.5);
    CHECK(mat_get(&m, 1, 2) == 4.5);

    Vec v = vec_zeros(&a, 4);
    CHECK(v.len == 4);
    CHECK(v.data[3] == 0.0);

    /* add / sub / scale on 2x2 matrices */
    Mat x = mat_alloc(&a, 2, 2);
    mat_set(&x, 0, 0, 1.0); mat_set(&x, 0, 1, 2.0);
    mat_set(&x, 1, 0, 3.0); mat_set(&x, 1, 1, 4.0);

    Mat y = mat_alloc(&a, 2, 2);
    mat_set(&y, 0, 0, 5.0); mat_set(&y, 0, 1, 6.0);
    mat_set(&y, 1, 0, 7.0); mat_set(&y, 1, 1, 8.0);

    Mat sum = mat_add(&a, &x, &y);
    CHECK(mat_get(&sum, 0, 0) == 6.0);
    CHECK(mat_get(&sum, 1, 1) == 12.0);

    Mat diff = mat_sub(&a, &y, &x);
    CHECK(mat_get(&diff, 0, 1) == 4.0);
    CHECK(mat_get(&diff, 1, 0) == 4.0);

    Mat scaled = mat_scale(&a, &x, 2.0);
    CHECK(mat_get(&scaled, 0, 1) == 4.0);
    CHECK(mat_get(&scaled, 1, 1) == 8.0);

    /* matmul: (2x3)(3x2) = (2x2), plus transpose */
    Mat p = mat_alloc(&a, 2, 3);
    for (usize i = 0; i < 6; i++) p.data[i] = (f64)(i + 1); /* 1..6 */
    Mat q = mat_alloc(&a, 3, 2);
    for (usize i = 0; i < 6; i++) q.data[i] = (f64)(i + 1); /* 1..6 */

    Mat prod = mat_matmul(&a, &p, &q);
    CHECK(prod.rows == 2 && prod.cols == 2);
    CHECK(mat_get(&prod, 0, 0) == 22.0); /* 1*1 + 2*3 + 3*5 */
    CHECK(mat_get(&prod, 0, 1) == 28.0); /* 1*2 + 2*4 + 3*6 */
    CHECK(mat_get(&prod, 1, 0) == 49.0); /* 4*1 + 5*3 + 6*5 */
    CHECK(mat_get(&prod, 1, 1) == 64.0); /* 4*2 + 5*4 + 6*6 */

    Mat pt = mat_transpose(&a, &p);
    CHECK(pt.rows == 3 && pt.cols == 2);
    CHECK(mat_get(&pt, 2, 1) == mat_get(&p, 1, 2));
    CHECK(mat_get(&pt, 0, 1) == mat_get(&p, 1, 0));

    /* dot / norm / elementwise mul / elementwise div */
    Vec u = vec_alloc(&a, 3);
    u.data[0] = 1.0; u.data[1] = -2.0; u.data[2] = 2.0;
    Vec w = vec_alloc(&a, 3);
    w.data[0] = 4.0; w.data[1] = 5.0; w.data[2] = 6.0;

    CHECK(vec_dot(&u, &w) == 6.0); /* 1*4 + -2*5 + 2*6 */
    CHECK(vec_norm1(&u) == 5.0);   /* |1| + |-2| + |2| */
    CHECK(vec_norm2(&u) == 3.0);   /* sqrt(1 + 4 + 4) */

    Vec uw = vec_mul(&a, &u, &w);
    CHECK(uw.data[0] == 4.0 && uw.data[1] == -10.0 && uw.data[2] == 12.0);

    Vec wu = vec_div(&a, &w, &u);
    CHECK(wu.data[0] == 4.0 && wu.data[2] == 3.0);

    /* outer product: 2-vec by 3-vec -> 2x3 */
    Vec ov = vec_alloc(&a, 2);
    ov.data[0] = 2.0; ov.data[1] = 3.0;
    Mat outer = mat_outer(&a, &ov, &w);
    CHECK(outer.rows == 2 && outer.cols == 3);
    CHECK(mat_get(&outer, 0, 0) == 8.0);  /* 2*4 */
    CHECK(mat_get(&outer, 1, 2) == 18.0); /* 3*6 */

    arena_destroy(&a);
    return TEST_SUMMARY("matrix");
}
