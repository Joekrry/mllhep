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

    arena_destroy(&a);
    return TEST_SUMMARY("matrix");
}
