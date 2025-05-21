#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "translator_utils.h"


static void test_find_translation_known(void **state) { //если слово в словаре есть
    DictionaryEntry dict[] = {
        {"привет", "hello"},
        {"мир", "world"}
    };
    const char* result = find_translation("привет", dict, 2);
    assert_string_equal(result, "hello"); 
}

static void test_find_translation_unknown(void **state) { //нету
    DictionaryEntry dict[] = {
        {"кот", "cat"},
        {"собака", "dog"}
    };
    const char* result = find_translation("дом", dict, 2);
    assert_true(result == NULL);
}


//наборчик функций возвр длину утф8 символа в байтах
static void test_utf8_len_ascii(void **state) { 
    assert_int_equal(utf8_char_len('A'), 1); //A = 01000001
}

static void test_utf8_len_two_byte(void **state) {
    unsigned char c = 0xD0;  //0xD0 0x94 = Д = 11010000
    assert_int_equal(utf8_char_len(c), 2);
}

static void test_utf8_len_three_byte(void **state) {
    unsigned char c = 0xE2; //0xE2 0x82 0xAC = € = 1110...
    assert_int_equal(utf8_char_len(c), 3);
}

//проверка латиницы
static void test_is_utf8_letter_start_ascii(void **state) {
    assert_true(is_utf8_letter_start('A'));
    assert_true(is_utf8_letter_start('z'));
    assert_false(is_utf8_letter_start(' '));
}

static void test_is_utf8_letter_start_utf8(void **state) {
    assert_true(is_utf8_letter_start(0xD0)); //кириллица
}

//Тест перевода строки
static void test_translate(void **state) {
    DictionaryEntry dict[] = {
        {"привет", "hello"},
        {"мир", "world"}
    };
    char input[] = "привет мир!\n";
    char output[256] = {0};

    FILE* out = fmemopen(output, sizeof(output), "w");
    translate(input, out, dict, 2);
    fclose(out);

    assert_string_equal(output, "hello world!\n");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_find_translation_known),
        cmocka_unit_test(test_find_translation_unknown),
        cmocka_unit_test(test_utf8_len_ascii),
        cmocka_unit_test(test_utf8_len_two_byte),
        cmocka_unit_test(test_utf8_len_three_byte),
        cmocka_unit_test(test_is_utf8_letter_start_ascii),
        cmocka_unit_test(test_is_utf8_letter_start_utf8),
        cmocka_unit_test(test_translate),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
