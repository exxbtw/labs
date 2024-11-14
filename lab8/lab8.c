#include <stdio.h>
#include <string.h>
int main(){
    int N;
    printf("Введите размер матрицы: ");
    scanf("%d", &N); //ВВОДИМ ДАННЫЕ МАТРИЦЫ С КЛАВИАТУРЫ
    int matrix[N][N];
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("Введи элемент матрицы [%d][%d]: ",i,j); 
            scanf("%d",&matrix[i][j]);
        }
    }
    
    int ravno[N]; //ВВОДИМ ДАННЫЕ ПОСЛЕ РАВНО С КЛАВИАТУРЫ
    int n,m;
    for(n=0; n<N; n++){
        printf("Ввели элемент после равно [%d]: ",n);
        scanf("%d",&ravno[n]);
    }
    
    printf("Матрица:\n"); //ВЫВОДИМ МАТРИЦУ
    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d ",matrix[i][j]);
        }
    printf("\n");
    }
    
    printf("Значения после равно: \n"); //ВЫВОДИМ ДАННЫЕ ПОСЛЕ РАВНО
    for(n=0;n<N;n++){
            printf("%d ",ravno[n]);
    }
    printf("\n");
    int opredelitel=1; //НАХОДИМ ОПРЕДЕЛИТЕЛЬ
    if(N==2){
        opredelitel = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    }
    else if (N==3){
        opredelitel = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2]
                    * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] - (matrix[0][2]
                    * matrix[1][1] * matrix[2][0] + matrix[0][1] * matrix[1][0] * matrix[2][2]
                    + matrix[0][0] * matrix[1][2] * matrix[2][1]);
    }
    else {
        printf("Определитель не сделать");
    }


    if (N == 2) { // Находим x и y для 2x2
        int deltaX = ravno[0] * matrix[1][1] - ravno[1] * matrix[0][1]; 
        int deltaY = matrix[0][0] * ravno[1] - matrix[1][0] * ravno[0]; 

        double x = (double)deltaX / opredelitel; 
        double y = (double)deltaY / opredelitel; 

        printf("x = %lf, y = %lf\n", x, y); 
    }
    else if (N == 3){
        int deltaX = ravno[0] * matrix[1][1] * matrix[2][2] + matrix[0][1] *
              matrix[1][2] * ravno[2] + matrix[0][2] * ravno[1] * matrix[2][1] -
              (matrix[0][2] * matrix[1][1] * ravno[2] + matrix[0][1] * ravno[1] *
              matrix[2][2]+ravno[0] * matrix[1][2] * matrix[2][1]);
        int deltaY = matrix[0][0] * ravno[1] * matrix[2][2] + ravno[0] *
              matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * ravno[2] -
              (matrix[0][2] * ravno[1] * matrix[2][0] + ravno[0] * matrix[1][0] *
              matrix[2][2]+matrix[0][0]*matrix[1][2]*ravno[2]);      
        int deltaZ = matrix[0][0] * matrix[1][1] * ravno[2] + matrix[0][1] *
              ravno[1] * matrix[2][0] + ravno[0] * matrix[1][0] * matrix[2][1] -
              (ravno[0] * matrix[1][1] * matrix[2][0] + matrix[0][1] * matrix[1][0] *
              ravno[2] + matrix[0][0] * ravno[1] * matrix[2][1]);    
        double x = (double)deltaX / opredelitel; 
        double y = (double)deltaY / opredelitel;
        double z = (double)deltaZ / opredelitel; 
        printf("x = %lf, y = %lf\n, z = %lf\n", x, y, z); 
    }
    else{
        printf("Пока!");
    }
}



// int opredelitel=1; //НАХОДИМ ОПРЕДЕЛИТЕЛЬ
// matrix[i][i] = 0;
// for (i=0;i<N;i++){
    //opredelitel = opredelitel * matrix[i][i]; //главная диагональ[00][11][22]
//}
//printf("%d\n",opredelitel);