#include "test.h"

int main(void) {
    CHECK(sizeof(i8)  == 1);
    CHECK(sizeof(i16) == 2);
    CHECK(sizeof(i32) == 4);
    CHECK(sizeof(i64) == 8);

    CHECK(sizeof(u8)  == 1);
    CHECK(sizeof(u16) == 2);
    CHECK(sizeof(u32) == 4);
    CHECK(sizeof(u64) == 8);

    CHECK(sizeof(f32) == 4);
    CHECK(sizeof(f64) == 8);

    CHECK((i8)-1 < 0);
    CHECK((u8)-1 > 0);

    return TEST_SUMMARY("types");
}
