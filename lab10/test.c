#include <stdio.h>

struct parabola {
    int a;
    int b;
    int c;
};

struct parabola inicializeStruct(int a, int b, int c) { // Функция инициализации структуры
    struct parabola func = {a, b, c};
    return func;
}

// Функция для вывода всех парабол
void printParabolas(struct parabola func[], int m) {
    for (int i = 0; i < m; i++) {
        printf("Парабола %d: y = %dx^2 + %dx + %d\n", i + 1, func[i].a, func[i].b, func[i].c);
    }
}

int main() {
    int m; // Количество парабол
    int k = 0; // Количество парабол, имеющих минимум
    printf("Сколько парабол хотите ввести: \n");
    scanf("%d", &m);

    struct parabola func[m]; // Массив структур парабол

    for (int i = 0; i < m; i++) {
        int a, b, c;
        printf("Введи параметры для параболы %d:\n", i + 1);

        printf("a: \n");
        scanf("%d", &a);
        if (a < 0) {
            k = k + 1; // Увеличиваем k для парабол с минимумом
        }
        printf("b: \n");
        scanf("%d", &b);
        printf("c: \n");
        scanf("%d", &c);

        func[i] = inicializeStruct(a, b, c);
    }

    printf("Введенные параболы:\n");
    int highest = 0; // Храним значение максимального минимума
    int highestIndex = -1; // Индекс самой высокой параболы
    for (int i = 0; i < m; i++) {
        if (func[i].a < highest || highestIndex == -1) {
            highest = func[i].a;
            highestIndex = i;
        }
    }

    // Используем функцию для вывода парабол
    printParabolas(func, m);
    
    printf("Количество парабол с точкой минимума: %d\n", k);
    if (highestIndex != -1) {
        printf("Самая высокая парабола: %d\n", highestIndex + 1);
    } else {
        printf("Нет парабол с точкой минимума.\n");
    }

    return 0;
}