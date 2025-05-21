cmake_minimum_required(VERSION 3.10)
project(math_utils)

set(CMAKE_C_STANDARD 11)


include_directories(/usr/local/Cellar/cmocka/1.1.7/include)
link_directories(/usr/local/Cellar/cmocka/1.1.7/lib)

#подкл библиотеку из math_utils.c
add_library(math_utils src/math_utils.c)

#добавляем тест
add_executable(test_math_utils tests/test_math_utils.c)
target_link_libraries(test_math_utils math_utils cmocka)


