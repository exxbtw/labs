#include <stdio.h>
#include <stdlib.h>


int main() {
    int N, M;
    printf("Введите размер строки N: ");
    scanf("%d", &N);
    printf("Введите размер столбцов M: ");
    scanf("%d", &M);

    int matrix[N][M];
    int i, j;

    for(i=0;i<N;i++){ //ВВОДИМ МАТРИЦУ
        for(j=0;j<M;j++){
            printf("Введите элемент матрицы [%d][%d]: ",i,j); 
            scanf("%d",&matrix[i][j]);
        }
    }

    printf("Исходная матрица:\n"); //выводим исходную матрицу
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    int max = matrix[0][0]; //ищем макс элемент
    int Imax = 0, Jmax = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
                Imax = i;
                Jmax = j;
            }
        }
    }

    printf("\nМаксимальный элемент: %d, позиция: [%d][%d]\n", max, Imax, Jmax);
    
    int INsize = N; // сторона квадрата
    if (INsize > N || INsize > M){
        printf("Невозможно сформировать квадратную матрицу.\n");
        return 1;
    }

    printf("Размер квадратной матрицы: %d\n", INsize);

    int zeroCount = 0;
    for (i = 0; i < N && i < M; i++) { //считаем нули в побочной диагонали
        if (matrix[i][M - 1 - i] == 0) {
            zeroCount++;
        }
    }

    printf("Количество нулей в побочной диагонали: %d\n", zeroCount);


    for (i = 0; i < INsize; i++) { //умножаем кол-во нулей на матрицу квадратную
        for (j = 0; j < INsize; j++) {
            matrix[Imax - i][Jmax + j] *= zeroCount;
        }
    }

  
    for (i = 0; i < N; i++) { //возводим в модуль 
        for (j = 0; j < M; j++) {
            if (matrix[i][j] < 0) {
                matrix[i][j] = abs(matrix[i][j]);
            }
        }
    }


    printf("\nИзмененная матрица:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
