#include <stdio.h>
int main(){

    int A[6]={5,7,3,1,4,8};
    int B[6]={1,-4,-2,7,5};
    int C[6]={};
    for(int i=0; i<6; i++){
        C[i]=A[i]+B[i]; //складываем переменные
    }
    int maxrealA=A[0];
    for(int i=0; i<6; i+=2){ //цикл, реальные числа(1-ое,3-е,5-ое,7-ое)
        if(maxrealA<A[i]){
        maxrealA=A[i]; } //максимальное реальное А
    }
    int summinB = 0; 
    for(int i=1; i<6; i+=2){ //цикл, мнимые чисоа
        if(B[i]<0){ 
            summinB++; //суммирует мнимые < 0
        }
    }
    int sredneeC = 0;
    for(int i=0; i<6; i++){
        sredneeC= (sredneeC + C[i] / 6.0); // Находим сумму C, а затем делим на кол-во чисел в массиве(ср.ариф)

    }
    printf("Максимальная реальная часть А: %d\n", maxrealA);
    printf("Количество мнимых частей меньше 0: %d\n",summinB);
    printf("Среднее арифметическое С: %d\n", sredneeC);
}