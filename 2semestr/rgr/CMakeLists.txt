cmake_minimum_required(VERSION 3.10)
project(Translator)

set(CMAKE_C_STANDARD 99)


include_directories(${CMAKE_SOURCE_DIR})
include_directories(/usr/local/Cellar/cmocka/1.1.7/include)
link_directories(/usr/local/Cellar/cmocka/1.1.7/lib)

add_executable(translator
    translator.c
    translator_utils.c
)

add_executable(test_translator
    test_translator.c
    translator_utils.c
)

target_link_libraries(test_translator PRIVATE cmocka)

enable_testing()
add_test(NAME TranslatorTests COMMAND test_translator)
