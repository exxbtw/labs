#include <stdio.h>
#include <stdlib.h>


void printMatrix(int N, int M, int **matrix) { //ФУНКЦИЯ ВЫВОД МАТРИЦЫ
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {

    int N, M;

    printf("Введите количество строк N: ");
    scanf("%d", &N);
    printf("Введите количество столбцов M: ");
    scanf("%d", &M);

    //Выделяем память
    int **matrix = malloc(N * sizeof(int*)); // Выделяем массив указателей на строки, sizeof(int*) возвращает размер одного указателя на int в байтах
    for (int i = 0; i < N; i++) {
        matrix[i] = malloc(M * sizeof(int)); // Выделяем память под столбцы, каждый указатель matrix[i] указывает на массив из M элементов (одна строка матрицы).
    }


    printf("Введите элементы матрицы (%d x %d):\n", N, M);
    for (int i = 0; i < N; i++) {
         for (int j = 0; j < M; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nНачальная матрица:\n");
    printMatrix(N, M, matrix);

    int max = matrix[0][0]; //ИЩЕМ МАКС ЭЛЕМЕНТ
    int Imax = 0, Jmax = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
                Imax = i;
                Jmax = j;
            }
        }
    }

    int zeroCount = 0;
    for (int i = 0; i < N; i++) { //считаем нули в побочной диагонали
        for(i = 0; i < M; i++){
            if (matrix[i][M-1-i] == 0) {
                zeroCount++;
            }
        }
    }
    if (zeroCount == 0) {
        printf("\nВ побочной диагонали нет нулей. Матрица останется такой же.\n");
 
        // Освобождаем память, от утечек памяти
        for (int i = 0; i < N; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 0;
    }

    //РАЗМЕР КВАДРАТА
    int maxHeight = Imax + 1; //от максимального элемента вверх
    int maxWidth = M - Jmax;  //от максимального элемента вправо
    int kvadrat;
    if (maxHeight < maxWidth) {
        kvadrat = maxHeight;
    } else {
        kvadrat = maxWidth;
    }


    for (int i = Imax; i > Imax - kvadrat; i--) { //УМНОЖАЕМ КОЛВО НУЛЕЙ НА КВАДРАТ
        for (int j = Jmax; j < Jmax + kvadrat; j++) {
            matrix[i][j] *= zeroCount;
        }
    }


    for (int i = 0; i < N; i++) { //МОДУЛЬ
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] < 0) {
                matrix[i][j] = -matrix[i][j];
            }
        }
    }

    printf("\nИтоговая матрица:\n");
    printMatrix(N, M, matrix);

    // Освобождаем память
    for (int i = 0; i < N; i++) {
        free(matrix[i]); // Освобождаем каждую строку
    }
    free(matrix); // Освобождаем массив указателей

    return 0;
}