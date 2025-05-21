#include <stdio.h>
#include "abonent.h"

int main() {
    const char *filename = "Abonent.dat";
    int n;

    printf("Введите количество абонентов: ");
    scanf("%d", &n);

    addAbonents(filename, n);
    printAbonents(filename);
    searchAbonent(filename);
    return 0;
}
