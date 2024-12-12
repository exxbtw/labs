#include <stdio.h>
#include "zagolovokfiles.h"

int main() {
    int m; //количество парабол
    int k = 0; //количество парабол, имеющих MINIMUM
    printf("Сколько парабол хотите ввести: \n");
    scanf("%d", &m);

    struct parabola func[m]; //структурный массив размером m из парабол

    for (int i = 0; i < m; i++) {
        int a, b, c;
        printf("Введи параметры для параболы %d:\n", i + 1);
        
        printf("a: \n");
        scanf("%d", &a);
        if (a > 0) {
            k = k + 1;
        }
        
        printf("b: \n");
        scanf("%d", &b);
        printf("c: \n");
        scanf("%d", &c); 

        func[i] = inicializeStruct(a, b, c);
    }

    printf("Введенные параболы:\n");
    int highest = 0; // тут храним значение макс. минимума
    int a; // тут номер самой высокой параболы
    for (int i = 0; i < m; i++) {
        if (func[i].a > highest) {
            highest = func[i].a; // исправлено для корректного определения максимального значения
            a = i;
        }
    }
    
    printParabola(func, m);
    printf("Кол-во парабол с точкой минимума: %d\n", k);
    printf("Самая высокая парабола: %d\n", a + 1); // добавлено +1 для удобства пользователя
    
    return 0;
}