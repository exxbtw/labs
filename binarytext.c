#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_PHONE 20
#define MAX_ADDRESS 150

typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char address[MAX_ADDRESS];
} Abonent;

void addAbonents(const char *filename, int n) { //перезапись файла
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    Abonent abonent;
    for (int i = 0; i < n; i++) {
        printf("Введите ФИО: ");
        getchar(); //Очистка буфера, чтобы убрать оставшийся символ новой строки \n от предыдущего ввода, Если не очистить буфер, следующий fgets() сразу считает этот \n и завершится, пропуская ввод.
        fgets(abonent.name, MAX_NAME, stdin); //Считывает строку с клавиатуры (stdin) и сохраняет её в abonent.name, fgets() позволяет корректно обрабатывать строки с пробелами
        abonent.name[strcspn(abonent.name, "\n")] = 0; //Удаляет символ новой строки \n, который fgets() добавляет в конец строки. strcspn() возвращает индекс первого вхождения \n в строке, и этот символ заменяется на 0, терминальный нуль (\0) вместо \n
        
        printf("Введите номер телефона: ");
        fgets(abonent.phone, MAX_PHONE, stdin); 
        abonent.phone[strcspn(abonent.phone, "\n")] = 0;
    
        printf("Введите адрес: ");
        fgets(abonent.address, MAX_ADDRESS, stdin);
        abonent.address[strcspn(abonent.address, "\n")] = 0;
        
        if (fwrite(&abonent, sizeof(Abonent), 1, file) != 1) { //Записывает структуру abonent в бинарный файл. 1 — количество элементов для записи (1 структура за раз).  проверка != 1 означает "если запись не выполнена
            perror("Error writing file"); 
            fclose(file);
            exit(1);
        }
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
    getchar(); //Очистка буфера

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