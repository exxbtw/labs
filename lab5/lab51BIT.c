#include <stdio.h>

int main() {
    int n;
    printf("Введите число: \n");
    scanf("%d", &n);
    
    if (n > 0 && (n & (n - 1)) == 0) { //проверяем число. У любой степени двойки первая цифра в двоич. С.С. всегда равна 1 (4=100)
        printf("Число %d является степенью числа 2 \n", n); 
    } else {
        printf("Число %d не является степенью числа 2 \n", n);
    }

}
