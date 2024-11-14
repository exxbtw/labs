#include <stdio.h>
int main() {
    int N;
    printf("Введите размер матрицы: ");
    scanf("%d", &N);
    int ulitka[N][N];

    for (int i = 0; i < N; i++) { // Вводим пустую матрицу
        for (int j = 0; j < N; j++) {
            ulitka[i][j] = 0;
        }
    }
    
    int k = 1; // ЦИКЛ ДЛЯ ЗАПОЛНЕНИЯ
    int verh = 0; // Верхняя граница
    int niz = N - 1; // Нижняя граница    тк счет с нуля
    int left = 0; // Левая граница
    int right = N - 1; // Правая граница

    while (verh <= niz & left <= right) {

        for (int j = left; j <= right; j++) { // Заполняем верхнюю строку
            ulitka[verh][j] = k++;
        }
        verh++;

        for (int i = verh; i <= niz; i++) {  // Заполняем правый столбец
            ulitka[i][right] = k++;
        }
        right--;

        if (verh <= niz) {  // Заполняем нижнюю строку
            for (int j = right; j >= left; j--) { //ИДЕМ ОТ ПРАВОГО КРАЯ ВЛЕВО, ПОНИЖАЯ right N=6-1 (5,4,3,2,1)
                ulitka[niz][j] = k++;
            }
            niz--;
        }

        if (left <= right) { // Заполняем левый столбец
            for (int i = niz; i >= verh; i--) { //ИДЕМ ОТ НИЗА ВВЕРХ N=6-1 ([0][5],[0][4]...) понижая наш коэффицент
                ulitka[i][left] = k++;
            }
            left++;
        }
    }

    
    for (int i = 0; i < N; i++) { // Выводим этот ужас
        for (int j = 0; j < N; j++) {
            printf("%d ", ulitka[i][j]);
        }
        printf("\n");
    }
}
