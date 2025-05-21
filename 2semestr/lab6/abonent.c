#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abonent.h"

void addAbonents(const char *filename, int n) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    Abonent abonent;
    for (int i = 0; i < n; i++) {
        printf("Введите ФИО: ");
        getchar();
        fgets(abonent.name, MAX_NAME, stdin);
        abonent.name[strcspn(abonent.name, "\n")] = 0;

        printf("Введите номер телефона: ");
        fgets(abonent.phone, MAX_PHONE, stdin);
        abonent.phone[strcspn(abonent.phone, "\n")] = 0;

        printf("Введите адрес: ");
        fgets(abonent.address, MAX_ADDRESS, stdin);
        abonent.address[strcspn(abonent.address, "\n")] = 0;

        if (fwrite(&abonent, sizeof(Abonent), 1, file) != 1) {
            perror("Error writing file");
            fclose(file);
            exit(1);
        }
    }
    fclose(file);
}

void printAbonents(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    Abonent abonent;
    printf("Содержимое файла %s:\n", filename);
    while (fread(&abonent, sizeof(Abonent), 1, file) == 1) {
        printf("%s, %s, %s\n", abonent.name, abonent.phone, abonent.address);
    }
    fclose(file);
}

void searchAbonent(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    int choice;
    char vvod[MAX_ADDRESS];
    printf("Выберите поле для поиска: 1 - ФИО, 2 - Телефон, 3 - Адрес: ");
    scanf("%d", &choice);
    getchar();

    printf("Введите значение для поиска: ");
    fgets(vvod, MAX_ADDRESS, stdin);
    vvod[strcspn(vvod, "\n")] = 0;

    Abonent abonent;
    int found = 0;
    rewind(file);

    while (fread(&abonent, sizeof(Abonent), 1, file) == 1) {
        if ((choice == 1 && strcmp(abonent.name, vvod) == 0) ||
            (choice == 2 && strcmp(abonent.phone, vvod) == 0) ||
            (choice == 3 && strcmp(abonent.address, vvod) == 0)) {
            printf("Найден абонент: %s, %s, %s\n", abonent.name, abonent.phone, abonent.address);
            found = 1;
        }
    }

    if (!found) {
        printf("Абонент не найден.\n");
    }
    fclose(file);
}
