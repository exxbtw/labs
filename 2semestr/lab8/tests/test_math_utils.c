#include <stdarg.h> //переменное число аргументов(для чмочки)
#include <stddef.h> //определение типов и макросов(тоже для чмочки)
#include <setjmp.h> //нелокальные переходы
#include <cmocka.h>
#include "../src/math_utils.h"

static void test_add(void **state) { 
    (void)state;
    assert_int_equal(add(2, 3), 5); 
    assert_int_equal(add(-1, -1), -2);
}

static void test_subtract(void **state) {
    (void)state;
    assert_int_equal(subtract(5, 3), 1); 
    assert_int_equal(subtract(2, 5), -3);
}

static void test_multiply(void **state) {
    (void)state;
    assert_int_equal(multiply(4, 5), 20);
    assert_int_equal(multiply(0, 10), 0);
}

static void test_divide(void **state) { 
    (void)state;
    assert_int_equal(divide(10, 2), 5);
    assert_int_equal(divide(10, 0), 0); 
}

int main(void) {
    const struct CMUnitTest tests[] = { 
        cmocka_unit_test(test_add), 
        cmocka_unit_test(test_subtract),
        cmocka_unit_test(test_multiply),
        cmocka_unit_test(test_divide),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
