#include <stdio.h>
#include "zagolovokfiles.h"

struct parabola inicializeStruct(int a, int b, int c) { // функция инициализации структуры
    struct parabola func = {a, b, c};
    return func;
}

void printParabola(struct parabola func[], int m) {
    for (int i = 0; i < m; i++) {
        printf("Парабола %d: y = %dx^2 + %dx + %d\n", i + 1, func[i].a, func[i].b, func[i].c);
    }
}