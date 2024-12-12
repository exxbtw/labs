#include <stdio.h>

struct parabola{
    int a;
    int b;
    int c;

};

struct parabola inicializeStruct(int a, int b, int c) { 
    struct parabola func = {a, b, c};
    return func;
}

void printParabola(struct parabola func[], int m) {
    for (int i = 0; i < m; i++) {
        printf("Парабола %d: y = %dx^2 + %dx + %d\n", i + 1, func[i].a, func[i].b, func[i].c);
    }
}




int main(){
    int m; //колво парабол
    int k = 0; //колво парабол имеющих MINIMUM
    printf("Сколько парабол хотите ввести: \n");
    scanf("%d", &m);

   struct parabola func[m]; //структурный массив размером m из парабол

    for (int i = 0; i < m; i++) {
        int a, b, c;
        printf("Введи параметры для параболы %d:\n", i + 1);
        
        printf("a: \n");
        scanf("%d", &a);
        if(a>0){
            k=k+1;
        }
        else{
            k=k;
        }
        printf("b: \n");
        scanf("%d", &b);
        printf("c: \n");
        scanf("%d", &c); 

            func[i] = inicializeStruct(a, b, c);
    }

    printf("Введенные параболы:\n");
    int highest = 0; //тут храним значение макс. минимума
    int a; //тут номер самой высокой параболы
    for (int i = 0; i < m; i++) {
        if(func[i].a > highest){
            a = i;
        }
    }
    printParabola(func, m);
    printf("Кол-во парабол с точкой минимума: %d\n", k);
    printf("Самая высокая парабола: %d\n", a);
    
    
}



// if a > 0:
//    have min
// else
//    no min

// y=ax^2+bx+c
// m = int(input(кол-во парабол))
// k = count parabols with min
// if k > 0:
// find max(min) t.e. most high parabola